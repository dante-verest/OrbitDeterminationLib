#pragma once
#include "OrbitDeterminationMethods.h"

namespace Methods
{
    class EscobalMethod final :
        public OrbitDeterminationMethods
    {
    private:
        std::array<FPT, 3> m_C_psi{ 0.0 };
        Vector3<FPT> m_normOfr;
        std::array<FPT, 3> m_rho{ 0.0 };
        Matrix3<FPT> m_r;
        Vector3<FPT> m_W_tilda;
        std::array<std::array<FPT, 2>, 2> m_cos_v_j_minus_v_k, m_sin_v_j_minus_v_k{ 0.0 };
        FPT m_p = 0.0;
        std::array<FPT, 3> m_e_cos_v_i{ 0.0 };
        FPT m_e_sin_v_2 = 0.0;
        FPT m_e_square = 0.0;
        FPT m_a = 0.0;
        FPT m_sin_E_i_minus_E_j{ 0.0 }, m_cos_E_i_minus_E_j{ 0.0 };
        FPT m_sh_F_i_minus_F_j = 0.0, m_ch_F_i_minus_F_j = 0.0;
        FPT m_E_j_minus_E_i = 0.0, m_F_j_minus_F_i = 0.0;
        std::array<std::array<FPT, 2>, 3> m_F{ 0.0 }; // F(r, r); F(r + delta r, r); F(r, r + delta r)
        std::array<std::array<FPT, 2>, 2> m_delta_F_divide_on_delta_r{ 0.0 };

        void C_psi();  // 7.280
        void W_tilda(); // 7.283
        void cos_v_and_sin_v();
        void p();
        void e_and_a();
        void EllipticOrHyperbolicMotion(const std::size_t i);
        void Loop();
        void MethodsCalculateLoop() override;
        void r_2_and_v_2();
    public:
        EscobalMethod(
            const std::array<AngularMeasurements<FPT>, 3>& angularMeasurements,
            const std::array<Date, 3>& t,
            const std::array<ObservationPoint<FPT>, 3>& observationPoints,
            const bool isDebugFile = false);
    };
}

