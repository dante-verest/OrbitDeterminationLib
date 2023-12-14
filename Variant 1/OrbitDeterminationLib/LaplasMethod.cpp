#include "pch.h"
#include "LaplasMethod.h"

Methods::LaplasMethod::LaplasMethod(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	const bool isDebugFile) :
	OrbitDeterminationMethods(angularMeasurements, t, observationPoints, isDebugFile)
{
	this->DebugFile("Method name: Laplas\n");
};

void Methods::LaplasMethod::s()
{
	m_s[0] = m_tau3 / (m_tau1 * (m_tau1 - m_tau3));
	m_s[1] = -(m_tau3 + m_tau1) / (m_tau1 * m_tau3);
	m_s[2] = -m_tau1 / (m_tau3 * (m_tau3 - m_tau1));
	m_s[3] = 2 / (m_tau1 * (m_tau1 - m_tau3));
	m_s[4] = 2 / (m_tau1 * m_tau3);
	m_s[5] = 2 / (m_tau3 * (m_tau3 - m_tau1));
	this->DebugFile("\ns[1] = ", m_s[0], "\ns[2] = ", m_s[1], "\ns[3] = ", m_s[2],
		"\ns[4] = ", m_s[3], "\ns[5] = ", m_s[4], "\ns[6] = ", m_s[5], "\n");
};
void Methods::LaplasMethod::L_2_point_and_L_2_two_point()
{
	m_L_2_point_and_L_2_two_point[0] = m_s[0] * m_L.row(0) + m_s[1] * m_L.row(1) + m_s[2] * m_L.row(2);
	m_L_2_point_and_L_2_two_point[1] = m_s[3] * m_L.row(0) + m_s[4] * m_L.row(1) + m_s[5] * m_L.row(2);
	this->DebugFile("\nL2_point =\n", m_L_2_point_and_L_2_two_point[0], 
		"\nL2_point-point =\n", m_L_2_point_and_L_2_two_point[1], "\n");
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
		this->DebugFile("\nObservation points are different.\nR2_point =\n", m_R_2_point_and_R_2_two_point[0],
			"\nr2_point-point =\n", m_R_2_point_and_R_2_two_point[1], "\n");
	}
	else
	{
		m_R_2_point_and_R_2_two_point[0] = Vector3<FPT>(-m_R(1, 1), m_R(1, 0), 0) * 
			omega_Earth * M_PI / (180 * /*k * */from_day_to_minute);
		m_R_2_point_and_R_2_two_point[1] = Vector3<FPT>(-m_R(1, 0), -m_R(1, 1), 0) *
			omega_Earth * omega_Earth * 
			M_PI * M_PI / (180 * 180 * /*k * k * */from_day_to_minute * from_day_to_minute);
		this->DebugFile("\nObservation point is one.\nR2_point =\n", m_R_2_point_and_R_2_two_point[0],
			"\nr2_point-point =\n", m_R_2_point_and_R_2_two_point[1], "\n");
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
	this->DebugFile("\n", localMatrix, "\nDelta = ", m_det, "\n");
	localMatrix.row(2) = m_R_2_point_and_R_2_two_point[1];
	m_D_a = localMatrix.determinant();
	this->DebugFile("\n", localMatrix, "\nDa = ", m_D_a, "\n");
	localMatrix.row(2) = m_R.row(1);
	m_D_b = localMatrix.determinant();
	this->DebugFile("\n", localMatrix, "\nDb = ", m_D_b, "\n");
	localMatrix.row(1) = m_R_2_point_and_R_2_two_point[1];
	localMatrix.row(2) = m_L_2_point_and_L_2_two_point[1];
	m_D_c = localMatrix.determinant();
	this->DebugFile("\n", localMatrix, "\nDc = ", m_D_c, "\n");
	localMatrix.row(1) = m_R.row(1);
	m_D_d = localMatrix.determinant();
	this->DebugFile("\n", localMatrix, "\nDd = ", m_D_d, "\n");
};
void Methods::LaplasMethod::A_2_and_B_2_and_C_2_and_D_2_asterisks()
{
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] = 2 * m_D_a / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] = 2 * m_D_b / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[2] = m_D_c / m_det;
	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[3] = m_D_d / m_det;
	this->DebugFile("\nA2 = ", m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0],
		"\nB2 = ", m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1],
		"\nC2 = ", m_A_2_and_B_2_and_C_2_and_D_2_asterisks[2],
		"\nD2 = ", m_A_2_and_B_2_and_C_2_and_D_2_asterisks[3], "\n");
};
void Methods::LaplasMethod::R_2_2()
{
	m_R_2_2 = m_R.row(1).squaredNorm();
	this->DebugFile("\nR2^2 = ", m_R_2_2, "\n");
};
void Methods::LaplasMethod::C_psi()
{
	m_C_psi = -m_L.row(1).dot(m_R.row(1));
	this->DebugFile("\nC_psi = ", m_C_psi, "\n");
};
void Methods::LaplasMethod::EighthDegreeEquation()
{
	FPT a = 0.0, b = 0.0, c = 0.0; // коэффициенты уравнения 8-ой степени
	//a = -m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] * (m_C_psi + 
	//	m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] *  m_R_2_2);
	a = -m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] * (2 * m_C_psi +
		m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0]) - m_R_2_2;
	b = -2 * mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] * (m_C_psi + m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0]);
	c = -pow(mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1], 2);
	this->DebugFile("\nEighth degree equation with coefficients\na = ", a, ", b = ", b, " and c = ", c, "\n");
	std::size_t i = 0;
	FPT fLastResult = 0.0, fIterationResult = 0.0, fLocalDivide = 0.0;
	const IT nXSize = 100000;
	IT x[nXSize]{ 0 };
	for (i = 0; i < nXSize; i++)
		x[i] = static_cast<IT>(1000 * (i + 1));
	auto f = [](const FPT a, const FPT b, const FPT c, const FPT x)
	{
		return (pow(x, 8) + a * pow(x, 6) + b * pow(x, 3) + c);
	};
	fLastResult = f(a, b, c, x[0]);
	for (i = 1; i < nXSize; i++)
	{
		fIterationResult = f(a, b, c, x[i]);
		if (fIterationResult < 0 && fLastResult >= 0 ||
			fIterationResult >= 0 && fLastResult < 0)
		{
			m_r_2 = x[i];
			this->DebugFile("Inelegant solution: r2 = ", m_r_2, "\n");
			break;
		}
		fLastResult = fIterationResult;
	}
	do
	{
		fLocalDivide = f(a, b, c, m_r_2) / (8 * pow(m_r_2, 7) + 6 * a * pow(m_r_2, 5) + 3 * b * pow(m_r_2, 2));
		m_r_2 -= fLocalDivide;
	} while (fLocalDivide >= 1e-6);
	this->DebugFile("Elegant solution: r2 = ", m_r_2, "\n");
};
void Methods::LaplasMethod::rho_2_and_rho_2_point()
{
	m_rho_2_and_rho_2_point[0] = m_A_2_and_B_2_and_C_2_and_D_2_asterisks[0] +
		mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[1] / pow(m_r_2, 3);
	m_rho_2_and_rho_2_point[1] = m_A_2_and_B_2_and_C_2_and_D_2_asterisks[2] +
		mu * m_A_2_and_B_2_and_C_2_and_D_2_asterisks[3] / pow(m_r_2, 3);
	this->DebugFile("\nrho2 = ", m_rho_2_and_rho_2_point[0], "\nrho2_point = ", m_rho_2_and_rho_2_point[1], "\n");
};
void Methods::LaplasMethod::r_2_and_v_2()
{
	m_r_2_out = m_rho_2_and_rho_2_point[0] * m_L.row(1) - m_R.row(1);
	// из км/мин в км/с
	m_v_2_out = (m_rho_2_and_rho_2_point[1] * m_L.row(1).transpose() +
		m_rho_2_and_rho_2_point[0] * m_L_2_point_and_L_2_two_point[0] -
		m_R_2_point_and_R_2_two_point[0]) / 60;
	this->DebugFile("\nOutput result vectors:\nr2 =\n", m_r_2_out, "\nv2 =\n", m_v_2_out, "\n");
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