#include "pch.h"
#include "OrbitDeterminationMethods.h"

// ctors
Methods::OrbitDeterminationMethods::OrbitDeterminationMethods()
{};
Methods::OrbitDeterminationMethods::OrbitDeterminationMethods(
	const std::array<AngularMeasurements<FPT>, 3>& angularMeasurements,
	const std::array<Date, 3>& t,
	const std::array<ObservationPoint<FPT>, 3>& observationPoints)
{
	this->m_angularMeasurements = angularMeasurements;
	this->m_t = t;
	this->m_observationPoints = observationPoints;
	this->m_orbitalParameters = Structures::OrbitalParameters<FPT>();
};
// dtor
Methods::OrbitDeterminationMethods::~OrbitDeterminationMethods()
{
};

bool Methods::OrbitDeterminationMethods::
AreEqual(const FPT comparable, const FPT comparative, const FPT epsilon)
{
	return (std::fabs(comparable - comparative) <=
		epsilon * std::fmax(std::fabs(comparable), std::fabs(comparative)));
};
bool Methods::OrbitDeterminationMethods::
ComparisonLessThanCriteria(const FPT comparable, const FPT criteria)
{
	return (comparable < criteria);
};

void Methods::OrbitDeterminationMethods::tau1_and_tau3()
{
	for (std::size_t i = 0; i < 3; i++)
		m_JulianDate[i] = Date::JulianDate(m_t[i]);
	m_tau1 = ss_hh_dd * (m_JulianDate[0] - m_JulianDate[1]);
	m_tau3 = ss_hh_dd * (m_JulianDate[2] - m_JulianDate[1]);
};
void Methods::OrbitDeterminationMethods::L()
{
	for (std::size_t column = 0; column < 3; column++)
		m_L.row(column) = Vector3<FPT>(
			cos(m_angularMeasurements[column].delta) * cos(m_angularMeasurements[column].alpha),
			cos(m_angularMeasurements[column].delta) * sin(m_angularMeasurements[column].alpha),
			sin(m_angularMeasurements[column].delta));
};
void Methods::OrbitDeterminationMethods::G()
{
	for (std::size_t i = 0; i < 3; i++)
	{
		FPT sin_phi = sin(m_observationPoints[i].phi);
		FPT res = a_e /
			sqrt(1 - (2 * f - f * f) * sin_phi * sin_phi);
		m_G[i][0] = res + m_observationPoints[i].H;
		m_G[i][1] = res * (1 - f * f) + m_observationPoints[i].H;
	}
};
void Methods::OrbitDeterminationMethods::LocalSiderealTime_and_R()
{
	// число Юлианских веков
	FPT T_UT1 = (m_JulianDate[1] - 2451545) / 36525;
	// среднее звёздное время по Гринвичу
	FPT Theta_GST0 = 100.4606184 +
		36000.77005361 * T_UT1 +
		0.000387933 * pow(T_UT1, 2) -
		2.583e-8 * pow(T_UT1, 3);
	// приведение угловой величины к интервалу до 360 градусов
	Theta_GST0 = Theta_GST0 - static_cast<int>(Theta_GST0 / 360) * 360;
	FPT Theta_GST = 0.0;
	for (std::size_t i = 0; i < 3; i++)
	{
		// Гринвичское звёздное время, в градусах, время - в минутах
		Theta_GST = Theta_GST0 +
			omega_Earth * (m_t[i].hour + m_t[i].min / 60.0 + m_t[i].sec / 3600.0);
		// само местное звёздное время, в градусах
		m_Theta_LST[i] = Theta_GST + (m_observationPoints[i].lambda * 180 / M_PI);
		// звёздное время в радианы
		m_Theta_LST[i] = m_Theta_LST[i] * M_PI / 180;
		// Ri: Xi, Yi, Zi
		m_R.row(i) = Vector3<FPT>(
			-m_G[i][0] * cos(m_observationPoints[i].phi) * cos(m_Theta_LST[i]),
			-m_G[i][0] * cos(m_observationPoints[i].phi) * sin(m_Theta_LST[i]),
			-m_G[i][1] * sin(m_observationPoints[i].phi));
	}
};
void Methods::OrbitDeterminationMethods::OrbitalParameters()
{
	const FPT twoM_PI = 2 * M_PI;
	FPT normOfr = 0.0, normOfv = 0.0;
	FPT v_r = 0.0;
	Vector3<FPT> h;
	Vector3<FPT> N;
	Vector3<FPT> e;
	FPT normOfN = 0.0;
	//m_orbitalParameters.a = m_a; // большая полуось
	normOfr = m_r_2_out.norm(); // 1
	normOfv = m_v_2_out.norm(); // 2
	v_r = m_r_2_out.dot(m_v_2_out) / normOfr; // 3
	h = m_r_2_out.cross(m_v_2_out); // 4
	m_orbitalParameters.h = h.norm(); // 5
	m_orbitalParameters.i = acos(h[2] / m_orbitalParameters.h); // 6
	N = h.cross(Vector3<FPT>(0, 0, 1)); // 7
	normOfN = N.norm(); // 8
	if (ComparisonLessThanCriteria(N[1], 0)) // 9
		m_orbitalParameters.Omega = twoM_PI - acos(N[0] / normOfN);
	else
		m_orbitalParameters.Omega = acos(N[0] / normOfN);
	e = ((normOfv * normOfv - mu / normOfr) * m_r_2_out - normOfr * v_r * m_v_2_out) / mu; // 10
	m_orbitalParameters.e = e.norm(); // 11
	m_orbitalParameters.a = m_orbitalParameters.h * m_orbitalParameters.h /
		(mu * (1 - m_orbitalParameters.e * m_orbitalParameters.e)); // большая полуось
	if (ComparisonLessThanCriteria(e[2], 0)) // 12
		m_orbitalParameters.omega = twoM_PI - acos(N.dot(e) / (normOfN * m_orbitalParameters.e));
	else
		m_orbitalParameters.omega = acos(N.dot(e) / (normOfN * m_orbitalParameters.e));
	if (ComparisonLessThanCriteria(v_r, 0)) // 13
		m_orbitalParameters.Theta = twoM_PI - acos(e.dot(m_r_2_out) / (m_orbitalParameters.e * normOfr));
	else
		m_orbitalParameters.Theta = acos(e.dot(m_r_2_out) / (m_orbitalParameters.e * normOfr));
};


void Methods::OrbitDeterminationMethods::TemplateMethod()
{
	tau1_and_tau3();
	L();
	G();
	LocalSiderealTime_and_R();
	MethodsCalculateLoop();
	OrbitalParameters();
};
const Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& 
Methods::OrbitDeterminationMethods::get_r_2() const
{
	return m_r_2_out;
};
const Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& 
Methods::OrbitDeterminationMethods::get_v_2() const
{
	return m_v_2_out;
};
const Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& 
Methods::OrbitDeterminationMethods::getOrbitalParameters() const
{
	return m_orbitalParameters;
};