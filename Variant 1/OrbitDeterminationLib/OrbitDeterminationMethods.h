#pragma once
#include "pch.h"
//#include "Eigen/Core"
#include "Date.h"
#include "OrbitalParameters.h"
#include "AngularMeasurements.h"
#include "./ObservationPoint.h"

namespace Methods
{
	using namespace Eigen;
	using namespace Structures;

	//template<typename T>
	//concept FPT = std::is_floating_point<T>::value;
	//template<typename T>
	//concept IT = std::is_integral<T>::value;

	class OrbitDeterminationMethods
	{
	public:
		using FPT = double;
		using IT = int;
		//const FPT M_PI = 3.415926535897932384626433832795; // число Пифагора
	protected:

		// constants
		const IT ss_hh_dd = 60 * 60 * 24;
		//const FPT k = 0.01720209895;			// постоянная Гаусса
		const FPT mu = 398600.4418;				// гравитационная постоянная Земли, в км/с
		const FPT a_e = 6378.270;				// экваториальный радиус Земли (по Херрику, Бейкеру и Хилтону), в км
		const FPT f = 1 / 298.3;				// коэффициент полярного сжатия Земли
		const FPT omega_Earth = 
			360.98564724; // угловая скорость Земли, в град/мин

		// input data
		std::array<AngularMeasurements<FPT>, 3> m_angularMeasurements;	// углы восхождения и склонения
		std::array<Date, 3> m_t;										// время наблюдения
		std::array<ObservationPoint<FPT>, 3> m_observationPoints;

		// output data
		Vector3<FPT> m_r_2_out, m_v_2_out;
		OrbitalParameters<FPT> m_orbitalParameters;

		// variables for calculations
		std::array<FPT, 3> m_JulianDate{ 0.0 };
		FPT m_tau1{ 0.0 }, m_tau3{ 0.0 };
		std::array<std::array<FPT, 2>, 3> m_G{ 0.0 };
		std::array<FPT, 3> m_Theta_LST{ 0.0 };
		Matrix3<FPT> m_L, m_R;
		//FPT m_a = 0.0;

		// methods, virtual - методы реализуются в дочерних классах
		void tau1_and_tau3(); // 7.104-7.105, 7.196-7.197, 7.274-7.275
		void L(); // 7.111-7.113, 7.199, 7.276
		void G(); // 7.115-7.116, 7.201, 7.277
		void LocalSiderealTime_and_R(); // 7.114, 7.117; 7.202, 7.203; 7.278, 7.279
		virtual void MethodsCalculateLoop() = 0; // 7.140-7.159; 7.200, 7.204-7.215; 7.281-7.322
		void OrbitalParameters();

		// вспомогательные методы
		bool AreEqual(const FPT comparable, const FPT comparative, const FPT epsilon);
		bool ComparisonLessThanCriteria(const FPT comparable, const FPT criteria);
	public:
		OrbitDeterminationMethods();
		OrbitDeterminationMethods(
			const std::array<AngularMeasurements<FPT>, 3>& angularMeasurements,
			const std::array<Date, 3>& t,
			const std::array<ObservationPoint<FPT>, 3>& observationPoints);
		virtual ~OrbitDeterminationMethods();
		void TemplateMethod();
		const Vector3<FPT>& get_r_2() const;
		const Vector3<FPT>& get_v_2() const;
		const Structures::OrbitalParameters<FPT>& getOrbitalParameters() const;
	};
}
