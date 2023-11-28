#pragma once

#ifdef ORBITDETERMINATIONLIB_EXPORTS
#define ORBITDETERMINATIONLIB_API __declspec(dllexport)
#else
#define ORBITDETERMINATIONLIB_API __declspec(dllimport)
#endif

#include "pch.h"
#include "GaussMethod.h"
#include "LaplasMethod.h"
#include "EscobalMethod.h"

extern "C" ORBITDETERMINATIONLIB_API void Gauss(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>&angularMeasurements,
	const std::array<Structures::Date, 3>&t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>&observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>&orbitalParameters);

extern "C" ORBITDETERMINATIONLIB_API void Laplas(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>&angularMeasurements,
	const std::array<Structures::Date, 3>&t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>&observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>&orbitalParameters);

extern "C" ORBITDETERMINATIONLIB_API void Escobal(
	const std::array<Structures::AngularMeasurements<Methods::OrbitDeterminationMethods::FPT>, 3>&angularMeasurements,
	const std::array<Structures::Date, 3>&t,
	const std::array<Structures::ObservationPoint<Methods::OrbitDeterminationMethods::FPT>, 3>&observationPoints,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&r_2,
	Eigen::Vector3<Methods::OrbitDeterminationMethods::FPT>&v_2,
	Structures::OrbitalParameters<Methods::OrbitDeterminationMethods::FPT>&orbitalParameters);