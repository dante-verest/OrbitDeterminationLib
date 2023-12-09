#pragma once
#include "OrbitDeterminationMethods.h"

namespace Methods
{
    class GaussMethod final :
        public OrbitDeterminationMethods
    {
    private:
        // variables
        FPT m_tau13 = 0.0;
        std::array<std::array<FPT, 2>, 3> m_A_and_B_asterisks{ 0.0 };
        Matrix3<FPT> m_L_minus_one_degree;
        std::array<Vector3<FPT>, 2> m_A_and_B; // A1, A2, A3; B1, B2, B3
        FPT m_C_psi = 0.0;
        FPT m_R_2_2 = 0.0;
        FPT m_r_2 = 0.0;
        FPT m_u_2 = 0.0;
        std::array<FPT, 2> m_D1D3{ 0.0 };
        Vector3<FPT> m_rho;
        Matrix3<FPT> m_r;
        FPT m_normOfr_2 = 0.0;
        FPT m_normOfr_2_point = 0.0;
        Vector3<FPT> m_r_2_point;
        std::array<FPT, 3> m_d{ 0.0 };
        FPT m_V_2 = 0.0;
        FPT m_a = 0.0;
        FPT m_f_1 = 0.0, m_f_3 = 0.0, m_g_1 = 0.0, m_g_3 = 0.0;
        FPT m_D_asterisk = 0.0;
        //std::array<FPT, 3> m_c{ 0.0 };
        Vector3<FPT> m_c;
        Vector3<FPT> m_G;
        Vector3<FPT> m_rho_n;

        // methods
        void tau13(); // 7.106
        void A_and_B(); // 7.107-7.110
        void L_minus_first_degree();  // 7.118-7.119
        void A_and_B_asterisks(); // 7.125
        void C_psi(); // 7.126
        void R_2_2(); // 7.127
        void EighthDegreeEquation();  // 7.131
        void u_2_and_D1D3();
        void rho();
        void HerrickGibbsFormulas(); // 7.141-7.148
        FPT f(const FPT V_2, const FPT r_2_length, const FPT r_2_length_point, const FPT tau); // 3.228
        FPT g(const FPT V_2, const FPT r_2_length, const FPT r_2_length_point, const FPT tau); // 3.229
        void Loop();
        void MethodsCalculateLoop() override;
        void r_2_and_v_2()/* override*/;
    public:
        GaussMethod(const std::array<AngularMeasurements<FPT>, 3>& angularMeasurements,
            const std::array<Date, 3>& t,
            const std::array<ObservationPoint<FPT>, 3>& observationPoints,
            const bool isDebugFile = false);
    };
}

