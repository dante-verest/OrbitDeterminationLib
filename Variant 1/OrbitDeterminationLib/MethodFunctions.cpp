#include "pch.h"
#include "MethodFunctions.h"

bool Method(
	const std::wstring& methodName,
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
	//if (strcmp(methodName, "Gauss") == 0)
	if(methodName == L"Метод Гаусса")
		method = std::make_unique<Methods::GaussMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	//else if (strcmp(methodName, "Laplas") == 0)
	else if (methodName == L"Метод Лапласа")
		method = std::make_unique<Methods::LaplasMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	//else if (strcmp(methodName, "Метод Эскобала") == 0)
	else if (methodName == L"Метод Эскобала")
		method = std::make_unique<Methods::EscobalMethod>(angularMeasurements, t, observationPoints, isDebugFile);
	else
		return false;
	method->TemplateMethod();
	r_2 = method->get_r_2();
	v_2 = method->get_v_2();
	orbitalParameters = method->getOrbitalParameters();
	std::copy(&method->getCalculateTime(), &method->getCalculateTime() + 1, calculateTime);
	if (orbitalParameters.IsEmpty())
		return false;
	else
		return true;

};