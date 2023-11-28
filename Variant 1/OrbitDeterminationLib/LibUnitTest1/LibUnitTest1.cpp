#include "pch.h"
#include "CppUnitTest.h"
#include "Date.h"
//#include "../../OrbitStructuresStaticLib/OrbitalParameters.h"
//#include "../../OrbitStructuresStaticLib/ObservationPoint.h"
//#include "../../OrbitStructuresStaticLib/AngularMeasurements.h"
#include "OrbitDeterminationMethods.h"
#include "MethodFunctions.h"
//#include "GaussMethod.h"
//#include "LaplasMethod.h"
//#include "EscobalMethod.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibUnitTest1
{
	using namespace Eigen;
	using namespace Structures;
	using namespace Methods;

	TEST_CLASS(LibUnitTest1)
	{
	private:
		using TAngularMeasurements = std::array<AngularMeasurements<OrbitDeterminationMethods::FPT>, 3>;
		using TDates = std::array<Date, 3>;
		using TObservationPoints = std::array<ObservationPoint<OrbitDeterminationMethods::FPT>, 3>;
		using TVector = Vector3<OrbitDeterminationMethods::FPT>;
		using TOrbitalParameters = OrbitalParameters<OrbitDeterminationMethods::FPT>;


		OrbitDeterminationMethods::FPT FromDegreesToRadians(const OrbitDeterminationMethods::FPT degrees)
		{
			return degrees * M_PI / 180;
		};
		OrbitDeterminationMethods::FPT FromDegMinSecMillisecToRadians(
			const OrbitDeterminationMethods::IT deg,
			const OrbitDeterminationMethods::IT min,
			const OrbitDeterminationMethods::FPT sec)
		{
			return (deg + min / 60 + sec / 3600) * M_PI / 180;
		};


		TVector r_2;
		TVector v_2;
		TOrbitalParameters orbitalParameters;


		const TAngularMeasurements angularMeasurements = {
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(0.939913), FromDegreesToRadians(18.667717)),
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(45.025748), FromDegreesToRadians(35.664741)),
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(67.886655), FromDegreesToRadians(36.996583)) };
		const TDates t = {
			Date(2012, 8, 20, 11, 40, 28.0),
			Date(2012, 8, 20, 11, 48, 28.0),
			Date(2012, 8, 20, 11, 52, 28.0) };
		const TObservationPoints observationPoints = {
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2),
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2),
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2) };



		/*std::tuple<const TAngularMeasurements&, const TDates&, const TObservationPoints&, 
			TVector&, TVector&, TOrbitalParameters&> testParameters1 = {
			const TAngularMeasurements{
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(0.939913), FromDegreesToRadians(18.667717)),
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(45.025748), FromDegreesToRadians(35.664741)),
			AngularMeasurements<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(67.886655), FromDegreesToRadians(36.996583)) },
		const TDates{
			Date(2012, 8, 20, 11, 40, 28.0),
			Date(2012, 8, 20, 11, 48, 28.0),
			Date(2012, 8, 20, 11, 52, 28.0) },
		const TObservationPoints{
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2),
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2),
			ObservationPoint<OrbitDeterminationMethods::FPT>(FromDegreesToRadians(40), FromDegreesToRadians(-110), 2) },
			r_2, v_2, orbitalParameters
		};*/

	public:
		
		TEST_METHOD(TestDateStructure)
		{
			Date date1(2012, 8, 20, 11, 40, 28.0);
			Date date2(2012, 8, 20, 11, 48, 28.0);
			Date date3(2012, 8, 20, 11, 52, 28.0);
			double julianDate2 = date2.JulianDate();
			Logger::WriteMessage(std::to_wstring(julianDate2).c_str());
			Assert::AreEqual(julianDate2, 2456159.991991, 1e-6);
			Date tau1 = date1 - date2;
			Date tau3 = date3 - date2;
			Assert::IsTrue((date1 - date2) == Date(0, 0, 0, 0, -8, 0.0));
		}

		TEST_METHOD(TestGaussMethod)
		{
			//std::apply(Gauss, testParameters1);
			//Logger::WriteMessage(std::to_wstring(std::get<3>(testParameters1)).c_str());
			Gauss(angularMeasurements, t, observationPoints, r_2, v_2, orbitalParameters);
			Logger::WriteMessage(L"r_2:");
			Logger::WriteMessage((std::to_wstring(r_2[0]) + L" i").c_str());
			Logger::WriteMessage((std::to_wstring(r_2[1]) + L" j").c_str());
			Logger::WriteMessage((std::to_wstring(r_2[2]) + L" k").c_str());
			Logger::WriteMessage(L"v_2:");
			Logger::WriteMessage((std::to_wstring(v_2[0]) + L" i").c_str());
			Logger::WriteMessage((std::to_wstring(v_2[1]) + L" j").c_str());
			Logger::WriteMessage((std::to_wstring(v_2[2]) + L" k").c_str());
			Logger::WriteMessage(L"Orbital parameters:");
			Logger::WriteMessage((L"a = " + std::to_wstring(orbitalParameters.a)).c_str());
			Logger::WriteMessage((L"e = " + std::to_wstring(orbitalParameters.e)).c_str());
			Logger::WriteMessage((L"h = " + std::to_wstring(orbitalParameters.h)).c_str());
			Logger::WriteMessage((L"i = " + std::to_wstring(orbitalParameters.i)).c_str());
			Logger::WriteMessage((L"Omega = " + std::to_wstring(orbitalParameters.Omega)).c_str());
			Logger::WriteMessage((L"omega = " + std::to_wstring(orbitalParameters.omega)).c_str());
			Logger::WriteMessage((L"Theta = " + std::to_wstring(orbitalParameters.Theta)).c_str());
		}

		/*TEST_METHOD(TestLaplasMethod)
		{

		}

		TEST_METHOD(TestEscobalMethod)
		{

		}*/
	};
}
