#pragma once
#include "stdafx.h"
#include "OrbitalParameters.h"
#include "Components.h"
#include "ConcreteMementoForOutputVectorsAndOrbitalParameters.h"

namespace Results
{
	class OutputVectorsAndOrbitalParameters : public Components
	{
		Q_OBJECT
	private:
		QString m_pMethodName;
		Vector3<double> m_r_2;
		Vector3<double> m_v_2;
		OrbitalParameters<double> m_orbitalParameters;
	public:
		OutputVectorsAndOrbitalParameters(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~OutputVectorsAndOrbitalParameters();

		void SetMethodName(const QString& aMethodName);
		const QString& GetMethodName();
		void Set_r_2(const Vector3<double>& r_2);
		const Vector3<double>& Get_r_2();
		void Set_v_2(const Vector3<double>& v_2);
		const Vector3<double>& Get_v_2();
		void SetOrbitalParameters(const OrbitalParameters<double>& aOrbitalParameters);
		const OrbitalParameters<double>& GetOrbitalParameters();

		QString FullFormOfVector(const Eigen::Vector3<double>& vector);
		void SetResultsToLineEdits();

		Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters* Save();
		void Restore(Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters* memento);

		void ClearAll();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:

	};
}
