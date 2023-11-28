#pragma once
#include "OrbitDeterminationMethods.h"

namespace Methods
{
    class LaplasMethod final :
        public OrbitDeterminationMethods
    {
    private:
        std::array<FPT, 6> m_s{ 0.0 };
        std::array<Vector3<FPT>, 2> m_L_2_point_and_L_2_two_point;
        std::array<Vector3<FPT>, 2> m_R_2_point_and_R_2_two_point;
        FPT m_det = 0.0, m_D_a = 0.0, m_D_b = 0.0, m_D_c = 0.0, m_D_d = 0.0;
        std::array<FPT, 4> m_A_2_and_B_2_and_C_2_and_D_2_asterisks{ 0.0 };
        FPT m_R_2_2 = 0.0;
        FPT m_C_psi = 0.0;
        FPT m_r_2 = 0.0;
        std::array<FPT, 2> m_rho_2_and_rho_2_point{ 0.0 };

        void s();  // 7.198
        void L_2_point_and_L_2_two_point();  // 7.200
        void R_2_point_and_R_2_two_point();  // 7.204
        void Determinations(); // 7.207
        void A_2_and_B_2_and_C_2_and_D_2_asterisks();
        void R_2_2();
        void C_psi(); // 7.209
        void EighthDegreeEquation(); // 7.211
        void rho_2_and_rho_2_point();
        void MethodsCalculateLoop() override;
        void r_2_and_v_2();
    public:
        LaplasMethod(
            const std::array<AngularMeasurements<FPT>, 3>& angularMeasurements,
            const std::array<Date, 3>& t,
            const std::array<ObservationPoint<FPT>, 3>& observationPoints);
    };
}

