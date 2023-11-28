#include "pch.h"
#include "MethodFunctions.h"

void Gauss(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters)
{
	Methods::GaussMethod *gaussMethod = new Methods::GaussMethod(angularMeasurements, t, observationPoints);
	gaussMethod->TemplateMethod();
	r_2 = gaussMethod->get_r_2();
	v_2 = gaussMethod->get_v_2();
	orbitalParameters = gaussMethod->getOrbitalParameters();
	delete gaussMethod;
};

void Laplas(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters)
{
	Methods::LaplasMethod* laplasMethod = new Methods::LaplasMethod(angularMeasurements, t, observationPoints);
	laplasMethod->TemplateMethod();
	r_2 = laplasMethod->get_r_2();
	v_2 = laplasMethod->get_v_2();
	orbitalParameters = laplasMethod->getOrbitalParameters();
	delete laplasMethod;
};

void Escobal(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>& angularMeasurements,
	const std::array<Structures::Date, 3>& t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>& observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>& v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>& orbitalParameters)
{
	Methods::EscobalMethod* escobalMethod = new Methods::EscobalMethod(angularMeasurements, t, observationPoints);
	escobalMethod->TemplateMethod();
	r_2 = escobalMethod->get_r_2();
	v_2 = escobalMethod->get_v_2();
	orbitalParameters = escobalMethod->getOrbitalParameters();
	delete escobalMethod;
};