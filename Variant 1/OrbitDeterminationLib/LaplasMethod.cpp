#include "pch.h"
#include "LaplasMethod.h"

Methods::LaplasMethod::LaplasMethod(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints) :
	OrbitDeterminationMethods(angularMeasurements, t, observationPoints)
{};

void Methods::LaplasMethod::s()
{
	m_s[0] = m_tau3 / (m_tau1 * (m_tau1 - m_tau3));
	m_s[1] = -(m_tau3 + m_tau1) / (m_tau1 * m_tau3);
	m_s[2] = -m_tau1 / (m_tau3 * (m_tau3 - m_tau1));
	m_s[3] = 2 / (m_tau1 * (m_tau1 - m_tau3));
	m_s[4] = 2 / (m_tau1 * m_tau3);
	m_s[5] = 2 / (m_tau3 * (m_tau3 - m_tau1));
};
void Methods::LaplasMethod::L_2_point_and_L_2_two_point()
{
	m_L_2_point_and_L_2_two_point[0] = m_s[0] * m_L.row(0) + m_s[1] * m_L.row(1) + m_s[2] * m_L.row(2);
	m_L_2_point_and_L_2_two_point[1] = m_s[3] * m_L.row(0) + m_s[4] * m_L.row(1) + m_s[5] * m_L.row(2);
};
void Methods::LaplasMethod::R_2_point_and_R_2_two_point()
{
	if (!AreEqual(m_observationPoints[0].phi, m_observationPoints[1].phi, 1e-6) &&
		!AreEqual(m_observationPoints[0].phi, m_observationPoints[2].phi, 1e-6) &&
		!AreEqual(m_observationPoints[0].lambda, m_observationPoints[1].lambda, 1e-6) &&
		!AreEqual(m_observationPoints[0].lambda, m_observationPoints[2].lambda, 1e-6))
	{
		m_R_2_point_and_R_2_two_point[0] = m_s[0] * m_R.row(0) + m_s[1] * m_R.row(1) + m_s[2] * m_R.row(2);
		m_R_2_point_and_R_2_two_point[1] = m_s[3] * m_R.row(0) + m_s[4] * m_R.row(1) + m_s[5] * m_R.row(2);
	}
	else
	{
		m_R_2_point_and_R_2_two_point[0] = Vector3<FPT>(-m_R(1, 1), m_R(1, 0), 0) * 
			omega_Earth * M_PI / (180 * 60);
		m_R_2_point_and_R_2_two_point[1] = Vector3<FPT>(-m_R(1, 0), -m_R(1, 1), 0) *
			omega_Earth * omega_Earth * M_PI * M_PI / (180 * 180 * 60 * 60);
	}
};
void Methods::LaplasMethod::Determinations()
{
	Matrix3<FPT> localMatrix;
	//localMatrix << m_L.row(1), m_L_2_point_and_L_2_two_point[0], m_L_2_point_and_L_2_two_point[1];
	localMatrix.row(0) = m_L.row(1);
	localMatrix.row(1) = m_L_2_point_and_L_2_two_point[0];
	localMatrix.row(2) = m_L_2_point_and_L_2_two_point[1];
	m_det = 2 * localMatrix.determinant();
	localMatrix.row(2) = m_R_2_point_and_R_2_two_point[1];
	m_D_a = localMatrix.determinant();
	localMatrix.row(2) = m_R.row(1);
	m_D_b = localMatrix.determinant();
	localMatrix.row(1) = m_R_2_point_and_R_2_two_point[1];
	localMatrix.row(2) = m_L_2_point_and_L_2_two_point[1];
	m_D_c = localMatrix.determinant();
	localMatrix.row(1) = m_R.row(1);
	m_D_d = localMatrix.determinant();
};
void Methods::LaplasMethod::A_2_and_B_2_and_C_2_and_D_2_asterisks()
{
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] = 2 * m_D_a / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] = 2 * m_D_b / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[2] = m_D_c / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[3] = m_D_d / m_det;
};
void Methods::LaplasMethod::R_2_2()
{
	m_R_2_2 = m_R.row(1).squaredNorm();
};
void Methods::LaplasMethod::C_psi()
{
	m_C_psi = 2 * m_L.row(1).dot(m_R.row(1));
};
void Methods::LaplasMethod::EighthDegreeEquation()
{
	FPT a = 0.0, b = 0.0, c = 0.0; // коэффициенты уравнения 8-ой степени
	a = -m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] * (m_C_psi + 
		m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] *  m_R_2_2);
	b = -mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] * (m_C_psi + 2 * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0]);
	c = -pow(mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1], 2);
	std::size_t i = 0;
	FPT fLastResult = 0.0, fIterationResult = 0.0, fLocalDivide = 0.0;
	const IT nXSize = 100;
	IT x[nXSize]{ 0 };
	for (i = 0; i < nXSize; i++)
		x[i] = static_cast<IT>(1000 * (i + 1));
	auto f = [&](const FPT a, const FPT b, const FPT c, const FPT x)
	{
		return (pow(x, 8) - a * pow(x, 6) - b * pow(x, 3) - c);
	};
	for (i = 0; i < nXSize; i++)
	{
		fIterationResult = f(a, b, c, x[i]);
		if (fIterationResult < 0 && fLastResult >= 0 ||
			fIterationResult >= 0 && fLastResult < 0)
		{
			m_r_2 = x[i];
			break;
		}
		fLastResult = fIterationResult;
	}
	do
	{
		fLocalDivide = f(a, b, c, m_r_2) / (8 * pow(m_r_2, 7) - 6 * a * pow(m_r_2, 5) - 3 * b * pow(m_r_2, 2));
		m_r_2 -= fLocalDivide;
	} while (fLocalDivide >= 1e-6);
};
void Methods::LaplasMethod::rho_2_and_rho_2_point()
{
	m_rho_2_and_rho_2_point[0] = m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] +
		mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] / pow(m_r_2, 3);
	m_rho_2_and_rho_2_point[1] = m_A_2_and_B_2_and_C_2_and_D_2_asterisks[2] +
		mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[3] / pow(m_r_2, 3);
};
void Methods::LaplasMethod::r_2_and_v_2()
{
	m_r_2_out = m_rho_2_and_rho_2_point[0] * (m_L.row(1) - m_R.row(1)).transpose();
	m_v_2_out = m_rho_2_and_rho_2_point[1] * m_L.row(1).transpose() +
		m_rho_2_and_rho_2_point[1] * m_L_2_point_and_L_2_two_point[0] -
		m_R_2_point_and_R_2_two_point[0];
};
void Methods::LaplasMethod::MethodsCalculateLoop()
{
	s();
	L_2_point_and_L_2_two_point();
	R_2_point_and_R_2_two_point();
	Determinations();
	A_2_and_B_2_and_C_2_and_D_2_asterisks();
	R_2_2();
	C_psi();
	EighthDegreeEquation();
	rho_2_and_rho_2_point();
	r_2_and_v_2();
};