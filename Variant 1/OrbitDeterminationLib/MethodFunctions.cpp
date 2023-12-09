#include "pch.h"
#include "MethodFunctions.h"

//bool Gauss(
//	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
//	const std::array<Structures::Date, 3>& t,
//	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
//	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters,
//	std::chrono::microseconds* calculateTime,
//	const bool isDebugFile)
//{
//	//Methods::GaussMethod *gaussMethod = new Methods::GaussMethod(angularMeasurements, t, observationPoints, isDebugFile);
//	std::unique_ptr<Methods::GaussMethod> gaussMethod =
//		std::make_unique<Methods::GaussMethod>(angularMeasurements, t, observationPoints, isDebugFile);
//	gaussMethod->TemplateMethod();
//	r_2 = gaussMethod->get_r_2();
//	v_2 = gaussMethod->get_v_2();
//	orbitalParameters = gaussMethod->getOrbitalParameters();
//	calculateTime = &gaussMethod->getCalculateTime();
//	if (orbitalParameters.IsEmpty())
//		return false;
//	else
//		return true;
//	//delete gaussMethod;
//};
//
//bool Laplas(
//	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
//	const std::array<Structures::Date, 3>& t,
//	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
//	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters,
//	std::chrono::microseconds* calculateTime,
//	const bool isDebugFile)
//{
//	//Methods::LaplasMethod* laplasMethod = new Methods::LaplasMethod(angularMeasurements, t, observationPoints, isDebugFile);
//	std::unique_ptr<Methods::LaplasMethod> laplasMethod =
//		std::make_unique<Methods::LaplasMethod>(angularMeasurements, t, observationPoints, isDebugFile);
//	laplasMethod->TemplateMethod();
//	r_2 = laplasMethod->get_r_2();
//	v_2 = laplasMethod->get_v_2();
//	orbitalParameters = laplasMethod->getOrbitalParameters();
//	calculateTime = &laplasMethod->getCalculateTime();
//	if (orbitalParameters.IsEmpty())
//		return false;
//	else
//		return true;
//	//delete laplasMethod;
//};
//
//bool Escobal(
//	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
//	const std::array<Structures::Date, 3>& t,
//	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
//	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
//	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters,
//	std::chrono::microseconds* calculateTime,
//	const bool isDebugFile)
//{
//	//Methods::EscobalMethod* escobalMethod = new Methods::EscobalMethod(angularMeasurements, t, observationPoints, isDebugFile);
//	std::unique_ptr<Methods::EscobalMethod> escobalMethod =
//		std::make_unique<Methods::EscobalMethod>(angularMeasurements, t, observationPoints, isDebugFile);
//	escobalMethod->TemplateMethod();
//	r_2 = escobalMethod->get_r_2();
//	v_2 = escobalMethod->get_v_2();
//	orbitalParameters = escobalMethod->getOrbitalParameters();
//	calculateTime = &escobalMethod->getCalculateTime();
//	if (orbitalParameters.IsEmpty())
//		return false;
//	else
//		return true;
//	//delete escobalMethod;
//};

bool Method(
	const char* methodName,
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters,
	std::chrono::microseconds* calculateTime,
	const bool isDebugFile)
{
	std::unique_ptr<Methods::OrbitDeterminationMethods> method;
	if (strcmp(methodName, "Gauss") == 0)
		method = std::make_unique<Methods::GaussMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	else if (strcmp(methodName, "Laplas") == 0)
		method = std::make_unique<Methods::LaplasMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	else if (strcmp(methodName, "Escobal") == 0)
		method = std::make_unique<Methods::EscobalMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	else
		return false;
	method->TemplateMethod();
	r_2 = method->get_r_2();
	v_2 = method->get_v_2();
	orbitalParameters = method->getOrbitalParameters();
	calculateTime = &method->getCalculateTime();
	if (orbitalParameters.IsEmpty())
		return false;
	else
		return true;

};