#pragma once
#include "stdafx.h"
#include "Components.h"
#include "AngularMeasurementsAndDate.h"
#include "FileResults.h"
#include "MeasurementMethod.h"
#include "ObservationPoints.h"
#include "GlobalButtons.h"
#include "ManuallyAngularMeasurementsAndDates.h"
#include "ManuallyObservationPoints.h"
#include "OutputVectorsAndOrbitalParameters.h"
#include "Menu.h"
#include "StatusBar.h"

using namespace Eigen;
using namespace Structures;


class ConcreteMediator1 : public Mediator
{
private:
	//Ui::OrbitDeterminationAppClass* m_pOrbitDeterminationAppClass;
	FirstInputParameters::AngularMeasurementsAndDate* m_pAngularMeasurementsAndDate;
	FirstInputParameters::FileResults* m_pFileResults;
	FirstInputParameters::MeasurementMethod* m_pMeasurementMethod;
	FirstInputParameters::ObservationPoints* m_pObservationPoints;
	SecondInputParameters::ManuallyAngularMeasurementsAndDate* m_pManuallyAngularMeasurementsAndDate;
	SecondInputParameters::ManuallyObservationPoints* m_pManuallyObservationPoints;
	Results::OutputVectorsAndOrbitalParameters* m_pOutputVectorsAndOrbitalParameters;
	Buttons::GlobalButtons* m_pGlobalButtons;
	Menu::Menu* m_pMenu;
	StatusBar::StatusBar* m_pStatusBar;

	//using FPT = double;
public:
	ConcreteMediator1(Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass);
	~ConcreteMediator1();
	void Notify(Components* sender, Commands event) override;
};

