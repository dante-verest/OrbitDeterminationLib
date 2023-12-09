#include "pch.h"
#include "EscobalMethod.h"

Methods::EscobalMethod::EscobalMethod(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	const bool isDebugFile) :
	OrbitDeterminationMethods(angularMeasurements, t, observationPoints, isDebugFile)
{};

void Methods::EscobalMethod::C_psi()
{
	for (std::size_t column = 0; column < 3; column++)
		m_C_psi[column] = -2 * m_L.row(column).dot(m_R.row(column));
};
void Methods::EscobalMethod::W_tilda()
{
	FPT fProductOf_r1r2_Norms = m_normOfr[0] * m_normOfr[1];
	//m_W_tilda[0] = (m_r(0, 1) * m_r(1, 2) - m_r(1, 1) * m_r(0, 2)) /
	//	fProductOf_r1r2_Norms;
	//m_W_tilda[1] = (m_r(1, 0) * m_r(0, 2) - m_r(0, 0) * m_r(1, 2)) /
	//	fProductOf_r1r2_Norms;
	//m_W_tilda[2] = (m_r(0, 0) * m_r(1, 1) - m_r(1, 0) * m_r(0, 1)) /
	//	fProductOf_r1r2_Norms;
	m_W_tilda = m_r.row(0).cross(m_r.row(1)) / fProductOf_r1r2_Norms;
};
void Methods::EscobalMethod::cos_v_and_sin_v()
{
	FPT x_k_y_j_minus_x_j_y_k = 0.0;
	for (std::size_t j = 1; j < 3; j++)
		for (std::size_t k = 0; k < j; k++)
		{
			m_cos_v_j_minus_v_k[j - 1][k] = m_r.row(j).dot(m_r.row(k)) /
				(m_normOfr[j] * m_normOfr[k]);
			x_k_y_j_minus_x_j_y_k = m_r(k, 0) * m_r(j, 1) - m_r(j, 0) * m_r(k, 1);
			m_sin_v_j_minus_v_k[j - 1][k] = x_k_y_j_minus_x_j_y_k *
				sqrt(1 - m_cos_v_j_minus_v_k[j - 1][k] * m_cos_v_j_minus_v_k[j - 1][k]) /
				abs(x_k_y_j_minus_x_j_y_k);
			if (m_W_tilda[2] < 0)
				m_sin_v_j_minus_v_k[j - 1][k] = -m_sin_v_j_minus_v_k[j - 1][k];
		}
};
void Methods::EscobalMethod::p()
{
	FPT c1 = 0.0, c3 = 0.0;
	if (AreEqual(acos(m_cos_v_j_minus_v_k[1][0]), M_PI, 1e-6) ||
		ComparisonLessThanCriteria(acos(m_cos_v_j_minus_v_k[1][0]), M_PI))
	{
		c1 = (m_normOfr[0] * m_sin_v_j_minus_v_k[1][0]) / (m_normOfr[1] * m_sin_v_j_minus_v_k[1][1]);
		c3 = (m_normOfr[0] * m_sin_v_j_minus_v_k[0][0]) / (m_normOfr[2] * m_sin_v_j_minus_v_k[1][1]);
		m_p = (m_normOfr[0] + c3 * m_normOfr[2] - c1 * m_normOfr[1]) / (1 + c3 - c1);
	}
	else
	{
		c1 = (m_normOfr[1] * m_sin_v_j_minus_v_k[1][1]) / (m_normOfr[0] * m_sin_v_j_minus_v_k[1][0]);
		c3 = (m_normOfr[1] * m_sin_v_j_minus_v_k[0][0]) / (m_normOfr[2] * m_sin_v_j_minus_v_k[1][0]);
		m_p = (c1 * m_normOfr[0] + c3 * m_normOfr[2] - m_normOfr[1]) / (c1 + c3 - 1);
	}
};
void Methods::EscobalMethod::e_and_a()
{
	for (std::size_t i = 0; i < 3; i++)
		m_e_cos_v_i[i] = m_p / m_normOfr[i] - 1;
	if (!AreEqual(acos(m_cos_v_j_minus_v_k[0][0]), M_PI, 1e-6))
		m_e_sin_v_2 = (-m_cos_v_j_minus_v_k[0][0] * m_e_cos_v_i[1] + m_e_cos_v_i[0]) / m_sin_v_j_minus_v_k[0][0];
	else
		m_e_sin_v_2 = (m_cos_v_j_minus_v_k[1][1] * m_e_cos_v_i[1] - m_e_cos_v_i[2]) / m_sin_v_j_minus_v_k[1][0];
	m_e_square = m_e_cos_v_i[1] * m_e_cos_v_i[1] + m_e_sin_v_2 * m_e_sin_v_2;
	m_a = m_p / (1 - m_e_square);
};
void Methods::EscobalMethod::EllipticOrHyperbolicMotion(const std::size_t row)
{
	std::size_t i = 0;
	FPT n = 0.0;
	FPT S_e = 0.0, C_e = 0.0, S_h = 0.0, C_h = 0.0;
	FPT M_j_minus_M_i{ 0.0 }; // M_1 - M_2, M_3 - M_2
	static std::array<FPT, 2> tau{ m_tau1, m_tau3 };
	if (ComparisonLessThanCriteria(m_e_square, 1))
	{
		n = sqrt(mu / pow(m_a, 3)); // 7.299
		S_e = m_normOfr[1] * sqrt(1 - m_e_square) * m_e_sin_v_2 / m_p; // 7.300
		C_e = m_normOfr[1] * (m_e_square + m_e_cos_v_i[1]) / m_p; // 7.301
		for (i = 0; i < 2; i++) 
		{
			m_sin_E_i_minus_E_j = m_normOfr[i + i] * m_sin_v_j_minus_v_k[i][i] / sqrt(m_a * m_p) +
				pow(-1, i) * m_normOfr[i + i] * (1 - m_cos_v_j_minus_v_k[i][i]) * S_e / m_p;
			m_cos_E_i_minus_E_j = 1 - m_normOfr[i + 1] * m_normOfr[i] * (1 - m_cos_v_j_minus_v_k[i][i]) /
				(m_a * m_p);
			m_E_j_minus_E_i = asin(m_sin_E_i_minus_E_j);
			M_j_minus_M_i = pow(-1, i + 1) * m_E_j_minus_E_i + 2 * S_e * pow(sin(m_E_j_minus_E_i / 2), 2) +
				pow(-1, i) * C_e * m_sin_E_i_minus_E_j;
			m_F[row][i] = tau[i] - M_j_minus_M_i / n;
		}
	}
	else
	{
		n = sqrt(mu / -pow(m_a, 3)); // 7.306
		S_h = m_normOfr[1] * sqrt(m_e_square - 1) * m_e_sin_v_2 / m_p; // 7.307
		C_h = m_normOfr[1] * (m_e_square + m_e_cos_v_i[1]) / m_p;
		for (i = 0; i < 2; i++)
		{
			m_sh_F_i_minus_F_j = m_normOfr[i + i] * m_sin_v_j_minus_v_k[i][i] / sqrt(- m_a * m_p) +
				pow(-1, i) * m_normOfr[i + i] * (1 - m_cos_v_j_minus_v_k[i][i]) * S_h / m_p; // 7.308
			m_ch_F_i_minus_F_j = 1 - m_normOfr[i + 1] * m_normOfr[i] * (1 - m_cos_v_j_minus_v_k[i][i]) /
				(m_a * m_p);
			m_F_j_minus_F_i = log(m_sh_F_i_minus_F_j + sqrt(m_sh_F_i_minus_F_j * m_sh_F_i_minus_F_j + 1)); // 7.309
			M_j_minus_M_i = pow(-1, i) * m_F_j_minus_F_i + 2 * S_h * pow(sinh(m_F_j_minus_F_i / 2), 2) +
				pow(-1, i + 1) * C_h * m_sh_F_i_minus_F_j; // 7.310
			m_F[row][i] = tau[i] - M_j_minus_M_i / n; // 7.311
		}
	}
};
void Methods::EscobalMethod::Loop()
{
	m_normOfr[0] = 1.00 * a_e;
	m_normOfr[1] = 1.10 * a_e;
	std::array<FPT, 2> normOfr_previous{ 0.0 };
	std::array<FPT, 2> delta_r{ 0.0 }, Delta_r{ 0.0 };
	FPT Delta = 0.0, Delta_1 = 0.0, Delta_2 = 0.0;
	for (std::size_t iter = 0; iter < 100000; iter++)
	{
		for (std::size_t j = 0; j < 3; j++)
		{
			switch (j)
			{
			case 1:
				normOfr_previous[0] = m_normOfr[0];
				delta_r[0] = normOfr_previous[0] * 0.04;
				m_normOfr[0] += delta_r[0];
				break;
			case 2:
				normOfr_previous[1] = m_normOfr[1];
				m_normOfr[0] = normOfr_previous[0];
				delta_r[1] = normOfr_previous[1] * 0.04;
				m_normOfr[1] += delta_r[1];
				break;
			}
			for (std::size_t i = 0; i < 2; i++)
			{
				m_rho[i] = (-m_C_psi[i] + sqrt(m_C_psi[i] * m_C_psi[i] -
					4 * (m_R.row(i).squaredNorm() - m_normOfr[i] * m_normOfr[i]))) / 2; // 7.281
				m_r.row(i) = m_rho[i] * m_L.row(i) - m_R.row(i); // 7.282
			}
			m_normOfr[0] = m_r.row(0).norm();
			m_normOfr[1] = m_r.row(1).norm();
			W_tilda(); // 7.283
			m_rho[2] = m_W_tilda.dot(m_R.row(2)) / m_W_tilda.dot(m_L.row(2)); // 7.284
			m_r.row(2) = m_rho[2] * m_L.row(2) - m_R.row(2); // 7.285
			m_normOfr[2] = m_r.row(2).norm(); // 7.286
			cos_v_and_sin_v();
			p();
			e_and_a();
			EllipticOrHyperbolicMotion(j);
		}
		for (std::size_t i = 0; i < 2; i++)
			for (std::size_t j = 0; j < 2; j++)
				m_delta_F_divide_on_delta_r[i][j] = (m_F[i + 1][j] - m_F[0][j]) / delta_r[i]; // 7.312-7.315
		Delta = m_delta_F_divide_on_delta_r[0][0] * m_delta_F_divide_on_delta_r[1][1] -
			m_delta_F_divide_on_delta_r[0][1] * m_delta_F_divide_on_delta_r[1][0]; // 7.316
		Delta_1 = m_delta_F_divide_on_delta_r[1][1] * m_F[0][0] -
			m_delta_F_divide_on_delta_r[1][0] * m_F[0][1]; // 7.317
		Delta_2 = m_delta_F_divide_on_delta_r[0][0] * m_F[0][1] -
			m_delta_F_divide_on_delta_r[0][1] * m_F[0][0]; // 7.318
		Delta_r[0] = -Delta_1 / Delta;
		Delta_r[1] = -Delta_2 / Delta;
		if (ComparisonLessThanCriteria(std::fabs(Delta_r[0]), 1e-6) &&
			ComparisonLessThanCriteria(std::fabs(Delta_r[1]), 1e-6))
			break;
		else
		{
			m_normOfr[1] = normOfr_previous[1];
			m_normOfr[0] += Delta_r[0];
			m_normOfr[1] += Delta_r[1];
		}
	}
};
void Methods::EscobalMethod::r_2_and_v_2()
{
	FPT f = 0.0, g = 0.0;
	if (ComparisonLessThanCriteria(m_e_square, 1))
	{
		m_r_2_out = m_r.row(1).transpose();
		f = 1 - m_a * (1 - m_cos_E_i_minus_E_j) / m_normOfr[1];
		g = m_tau3 - sqrt(pow(m_a, 3) / mu) * (m_E_j_minus_E_i - m_sin_E_i_minus_E_j);
		// èç êì/ìèí â êì/ñ
		m_v_2_out = (m_r.row(2).transpose() - f * m_r_2_out) / (g * 60);
	}
	else
	{
		m_r_2_out = m_r.row(1).transpose();
		f = 1 - m_a * (1 - m_ch_F_i_minus_F_j) / m_normOfr[1];
		g = m_tau3 - sqrt(pow(m_a, 3) / mu) * (m_F_j_minus_F_i - m_sh_F_i_minus_F_j);
		// èç êì/ìèí â êì/ñ
		m_v_2_out = (m_r.row(2).transpose() - f * m_r_2_out) / (g * 60);
	}
};
void Methods::EscobalMethod::MethodsCalculateLoop()
{
	C_psi();
	Loop();
	r_2_and_v_2();
};