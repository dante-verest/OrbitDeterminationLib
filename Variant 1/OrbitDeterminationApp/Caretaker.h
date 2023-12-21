#pragma once
#include "ManuallyAngularMeasurementsAndDates.h"
#include "ManuallyObservationPoints.h"
#include "OutputVectorsAndOrbitalParameters.h"
#include "ConcreteMementoForManuallyAngularMeasurementsAndDates.h"
#include "ConcreteMementoForManuallyObservationPoints.h"
#include "ConcreteMementoForOutputVectorsAndOrbitalParameters.h"

namespace Memento
{
	class Caretaker
	{
	private:
		using AngularMeasurementsAndDates = SecondInputParameters::ManuallyAngularMeasurementsAndDate;
		using ObservationPoints = SecondInputParameters::ManuallyObservationPoints;
		using Outputs = Results::OutputVectorsAndOrbitalParameters;

		QSettings m_mementosSettings;

		//std::vector<std::array<Memento*, 3>> m_pMementos;
		QVector<ConcreteMementoForManuallyAngularMeasurementsAndDates*> m_aAngularMeasurementsAndDates;
		QVector<ConcreteMementoForManuallyObservationPoints*> m_aObservationPoints;
		QVector<ConcreteMementoForOutputVectorsAndOrbitalParameters*> m_aOutputs;
		
		AngularMeasurementsAndDates* m_pManuallyAngularMeasurementsAndDates;
		ObservationPoints* m_pManuallyObservationPoints;
		Outputs* m_pOutputVectorsAndOrbitalParameters;
	public:
		Caretaker(
			AngularMeasurementsAndDates* aManuallyAngularMeasurementsAndDates,
			ObservationPoints* aManuallyObservationPoints,
			Outputs* aOutputVectorsAndOrbitalParameters);
		~Caretaker();

		void Backup();
		void Undo(int index);

		const QVector<ConcreteMementoForManuallyAngularMeasurementsAndDates*>& 
			GetVectorOfAngularMeasurementsAndDatesMementos();
		const QVector<ConcreteMementoForManuallyObservationPoints*>&
			GetVectorOfObservationPointsMementos();
		const QVector<ConcreteMementoForOutputVectorsAndOrbitalParameters*>&
			GetVectorOfOutputParametersMementos();
	private:
		void ReadSettings();
		void WriteSettings();
	};
}

