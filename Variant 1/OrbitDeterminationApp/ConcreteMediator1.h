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

using namespace Eigen;
using namespace Structures;


class ConcreteMediator1 : public Mediator
{
private:
	Ui::OrbitDeterminationAppClass* m_pOrbitDeterminationAppClass;
	FirstInputParameters::AngularMeasurementsAndDate* m_pAngularMeasurementsAndDate;
	FirstInputParameters::FileResults* m_pFileResults;
	FirstInputParameters::MeasurementMethod* m_pMeasurementMethod;
	FirstInputParameters::ObservationPoints* m_pObservationPoints;
	SecondInputParameters::ManuallyAngularMeasurementsAndDate* m_pManuallyAngularMeasurementsAndDate;
	SecondInputParameters::ManuallyObservationPoints* m_pManuallyObservationPoints;
	Results::OutputVectorsAndOrbitalParameters* m_pOutputVectorsAndOrbitalParameters;
	Buttons::GlobalButtons* m_pGlobalButtons;
	Menu::Menu* m_pMenu;

	//using FPT = double;

	std::string m_methodName;
	bool m_bIsCalculatingSuccess;
	std::array<AngularMeasurements<double>, 3> m_aAngularMeasurements;
	std::array<Date, 3> m_aDates;
	std::array<ObservationPoint<double>, 3> m_aPoints;
	std::array<bool, 3> m_aChoosedColumn;
	Vector3<double> m_r_2;
	Vector3<double> m_v_2;
	OrbitalParameters<double> m_orbitalParameters;
	std::chrono::microseconds m_calculateTime;
	bool m_bIsDebug;

	bool m_bIsConstObservationPoint;
	bool m_bIsOwnObservationPoint;
	//QString m_strTLEfilePath;
	//QString m_strOutputFilePath;
	//QMessageBox m_messageBox;
public:
	ConcreteMediator1(Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass);
	~ConcreteMediator1();
	void Notify(Components* sender, Commands event) override;
};

