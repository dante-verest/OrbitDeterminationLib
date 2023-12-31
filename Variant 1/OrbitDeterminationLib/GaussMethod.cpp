#include "pch.h"
#include "GaussMethod.h"

Methods::GaussMethod::GaussMethod(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints) :
	OrbitDeterminationMethods(angularMeasurements, t, observationPoints)
{};

void Methods::GaussMethod::tau13()
{
	m_tau13 = m_tau3 - m_tau1;
};
void Methods::GaussMethod::A_and_B()
{
	m_A_and_B[0][0] = m_tau3 / m_tau13;
	m_A_and_B[1][0] = m_A_and_B[0][0] * (m_tau13 * m_tau13 - m_tau3 * m_tau3) / 6;
	m_A_and_B[0][1] = -1.0;
	m_A_and_B[1][1] = 0.0;
	m_A_and_B[0][2] = -m_tau1 / m_tau13;
	m_A_and_B[1][2] = -m_A_and_B[0][2] * (m_tau13 * m_tau13 - m_tau1 * m_tau1) / 6;
};
void Methods::GaussMethod::L_minus_first_degree()
{
	m_L_minus_one_degree = m_L.reverse();
};
void Methods::GaussMethod::A_2_and_B_2_asterisks()
{
	for (std::size_t row = 0; row < 3; row++)
		for (std::size_t col = 0; col < 3; col++)
		{
			m_A_and_B_asterisks[row][0] -= (m_L_minus_one_degree(col, row) * m_R.col(col).dot(m_A_and_B[0]));
			m_A_and_B_asterisks[row][1] -= (m_L_minus_one_degree(col, row) * m_R.col(col).dot(m_A_and_B[1]));
		}
};
void Methods::GaussMethod::C_psi()
{
	// m_C_psi = 2 * m_L.col(1).dot(m_R.col(1));
	m_C_psi = -2 * (m_R(1, 0) * m_L(1, 0) + m_R(1, 1) * m_L(1, 1) + m_R(1, 2) * m_L(1, 2));
};
void Methods::GaussMethod::R_2_2()
{
	m_R_2_2 = m_R.row(1).squaredNorm();
};
void Methods::GaussMethod::EighthDegreeEquation()
{
	FPT a = 0.0, b = 0.0, c = 0.0; // ������������ ��������� 8-�� �������
	a = -m_A_and_B_asterisks[1][0] * (m_C_psi + m_A_and_B_asterisks[1][0] * m_R_2_2);
	b = -mu * m_A_and_B_asterisks[1][1] * (m_C_psi + 2 * m_A_and_B_asterisks[1][0]);
	c = -pow(mu * m_A_and_B_asterisks[1][1], 2);
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
void Methods::GaussMethod::u_2_and_D1D3()
{
	m_u_2 = mu / pow(m_r_2, 3);
	m_D1D3[0] = m_A_and_B[0][0] + m_A_and_B[1][0] * m_u_2;
	m_D1D3[1] = m_A_and_B[0][2] + m_A_and_B[1][2] * m_u_2;
};
void Methods::GaussMethod::rho()
{
	m_rho[0] = (m_A_and_B_asterisks[0][0] + m_A_and_B_asterisks[0][1] * m_u_2) / m_D1D3[0];
	m_rho[1] = m_A_and_B_asterisks[1][0] + m_A_and_B_asterisks[1][1] * m_u_2;
	m_rho[2] = (m_A_and_B_asterisks[2][0] + m_A_and_B_asterisks[2][1] * m_u_2) / m_D1D3[1];
};
void Methods::GaussMethod::HerrickGibbsFormulas()
{
	m_normOfr_2 = m_r.row(1).norm(); // 7.145
	m_d[0] = m_tau3 * (mu / (12 * pow(m_r.row(0).norm(), 3)) - 1 / (m_tau1 * m_tau13)); // 7.141
	m_d[1] = (m_tau1 + m_tau3) * (mu / (12 * pow(m_normOfr_2, 3)) - 1 / (m_tau1 * m_tau3)); // 7.142
	m_d[2] = -m_tau1 * (mu / (12 * pow(m_r.row(2).norm(), 3)) + 1 / (m_tau3 * m_tau13)); // 7.143
	m_r_2_point = -m_d[0] * m_r.row(0) + m_d[1] * m_r.row(1) - m_d[2] * m_r.row(2); // 7.144
	m_normOfr_2_point = m_r.row(1).dot(m_r_2_point) / m_normOfr_2; // 7.146
	m_V_2 = m_r_2_point.norm(); // 7.147
	m_a = 1 / (2 / m_normOfr_2 - m_V_2 * m_V_2 / mu); // 7.148
};
Methods::GaussMethod::FPT Methods::GaussMethod::f(const FPT V_2_norm, const FPT r_2_norm, const FPT r_2_point_norm, const FPT tau)
{
	FPT u_0 = mu / pow(r_2_norm, 3); // 3.212
	FPT p_0 = r_2_point_norm * r_2_norm / pow(r_2_norm, 2); // 3.218
	FPT q_0 = (pow(V_2_norm, 2) - pow(r_2_norm, 2) * u_0) / pow(r_2_norm, 2); // 3.219
	return (1 - u_0 * pow(tau, 2) / 2 + u_0 * p_0 * pow(tau, 3) / 2 +
		(3 * u_0 * q_0 - 15 * u_0 * pow(p_0, 2) + pow(u_0, 2)) * pow(tau, 4) / 24 +
		(7 * u_0 + pow(p_0, 3) - 3 * u_0 * p_0 * q_0 - pow(u_0, 2) * p_0) * pow(tau, 5) / 8 +
		(630 * u_0 * pow(p_0, 2) * q_0 - 24 * pow(u_0, 2) * q_0 - pow(u_0, 3) - 45 * u_0 * pow(q_0, 2) - 945 * u_0 * pow(p_0, 4) + 210 * pow(u_0 * p_0, 2) * pow(tau, 6) / 720) +
		(882 * pow(u_0, 2) * p_0 * q_0 - 3150 * pow(u_0, 2) * pow(p_0, 3) - 9450 * u_0 * pow(p_0, 3) * q_0 + 1575 * u_0 * p_0 * pow(q_0, 2) + 63 * pow(u_0, 3) * p_0 + 10395 * u_0 * pow(p_0, 5)) * pow(tau, 7) / 5040 +
		(1107 * pow(u_0 * q_0, 2) - 24570 * pow(u_0 * p_0, 2) * q_0 - 2205 * pow(u_0, 3) * pow(p_0, 2) + 51975 * pow(u_0, 2) * pow(p_0, 4) - 42525 * u_0 * pow(p_0 * q_0, 2) + 155925 * u_0 * pow(p_0, 4) * q_0 + 1575 * u_0 * pow(q_0, 3) + 117 * pow(u_0, 3) * q_0 - 135135 * u_0 * pow(p_0, 3) + pow(u_0, 4)) * pow(tau, 8) / 40320);
};
Methods::GaussMethod::FPT Methods::GaussMethod::g(const FPT V_2_norm, const FPT r_2_norm, const FPT r_2_point_norm, const FPT tau)
{
	FPT u_0 = mu / pow(r_2_norm, 3); // 3.212
	FPT p_0 = r_2_point_norm * r_2_norm / pow(r_2_norm, 2); // 3.218
	FPT q_0 = (pow(V_2_norm, 2) - pow(r_2_norm, 2) * u_0) / pow(r_2_norm, 2); // 3.219
	return (tau - u_0 * pow(tau, 3) / 6 + u_0 * p_0 * pow(tau, 4) / 4 + (9 * u_0 * q_0 - 45 * u_0 * pow(p_0, 2) + pow(u_0, 2)) * pow(tau, 5) / 120 +
		(210 * u_0 * pow(p_0, 3) - 90 * u_0 * p_0 * q_0 - 15 * pow(u_0, 2) * p_0) * pow(tau, 6) / 360 +
		(3150 * u_0 * pow(p_0, 2) * q_0 - 54 * pow(u_0, 2) * q_0 - 225 * u_0 * pow(q_0, 2) - 4725 * u_0 * pow(p_0, 4) + 630 * pow(u_0 * p_0, 2) - pow(u_0, 3)) * pow(tau, 7) / 5040 +
		(3024 * pow(u_0, 2) * p_0 * q_0 - 12600 * pow(u_0, 2) * pow(p_0, 3) - 56700 * u_0 * pow(p_0, 3) * q_0 + 9450 * u_0 * p_0 * pow(q_0, 2) + 62370 * u_0 * pow(p_0, 5) + 126 * pow(u_0, 3) * p_0) * pow(tau, 8) / 40320);
};
void Methods::GaussMethod::Loop()
{
	std::size_t i = 0;
	while (true)
	{
		for (i = 0; i < 3; i++)
			m_r.row(i) = m_rho[i] * m_L.row(i) - m_R.row(i);
		HerrickGibbsFormulas();
		m_f_1 = f(m_V_2, m_normOfr_2, m_normOfr_2_point, m_tau1);
		m_g_1 = g(m_V_2, m_normOfr_2, m_normOfr_2_point, m_tau1);
		m_f_3 = f(m_V_2, m_normOfr_2, m_normOfr_2_point, m_tau3);
		m_g_3 = g(m_V_2, m_normOfr_2, m_normOfr_2_point, m_tau3);
		m_D_asterisk = m_f_1 * m_g_3 - m_f_3 * m_g_1;
		m_c[0] = m_g_3 / m_D_asterisk;
		m_c[1] = -1.0;
		m_c[2] = -m_g_1 / m_D_asterisk;
		m_G = m_c[0] * m_R.row(0) + m_c[1] * m_R.row(1) + m_c[2] * m_R.row(2);
		m_rho_n[0] = m_G.dot(m_L_minus_one_degree.col(0)) / m_c[0];
		m_rho_n[1] = m_G.dot(m_L_minus_one_degree.col(1)) / m_c[1];
		m_rho_n[2] = m_G.dot(m_L_minus_one_degree.col(2)) / m_c[2];
		if (ComparisonLessThanCriteria(std::fabs(m_rho_n[0] - m_rho[0]), 1e-6) &&
			ComparisonLessThanCriteria(std::fabs(m_rho_n[1] - m_rho[1]), 1e-6) &&
			ComparisonLessThanCriteria(std::fabs(m_rho_n[2] - m_rho[2]), 1e-6))
			break;
		else
			m_rho = m_rho_n;
	}
};
void Methods::GaussMethod::r_2_and_v_2()
{
	m_r_2_out = m_rho_n - m_R.row(1).transpose();
	m_v_2_out = (- m_d[0] * m_r.row(0) + m_d[1] * m_r.row(1) + m_d[2] * m_r.row(2)).transpose();
};
void Methods::GaussMethod::MethodsCalculateLoop()
{
	tau13();
	A_and_B();
	L_minus_first_degree();
	A_2_and_B_2_asterisks();
	C_psi();
	R_2_2();
	EighthDegreeEquation();
	u_2_and_D1D3();
	rho();
	Loop();
	r_2_and_v_2();
};