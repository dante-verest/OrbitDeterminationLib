#pragma once
#include "stdafx.h"
#include "OrbitalParameters.h"
#include "Components.h"

namespace Results
{
	class OutputVectorsAndOrbitalParameters : public Components
	{
		Q_OBJECT
	public:
		OutputVectorsAndOrbitalParameters(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~OutputVectorsAndOrbitalParameters();
		QString FullFormOfVector(const Eigen::Vector3<double>& vector);
		void SetResultsToLineEdits(
			const Eigen::Vector3<double>& r_2,
			const Eigen::Vector3<double>& v_2,
			const Structures::OrbitalParameters<double>& orbitalParameters);
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:

	};
}
