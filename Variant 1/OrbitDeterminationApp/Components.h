#pragma once
#include "stdafx.h"
#include "ui_OrbitDeterminationApp.h"
#include "Mediator.h"

enum Commands
{
	// MeasurementMethod class
	ChoosingGaussMethod,
	ChoosingLaplasMethod,
	ChoosingEscobalMethod,
	// ObservationPoints class
	SettingConstObservationPoint,
	ChoosingMinskPoint,
	ChoosingFirstColumn,
	ChoosingSecondColumn,
	ChoosingThirdColumn,
	AddingColumn,
	SettingOwnObservationPoint,
	// AngularMeasurementsAndDate class
	SettingManually,
	SettingReadFromFile,
	SettingReadFromTLEfile,
	AddingTLEfilePath,
	// FileResults class
	AddingOutputFilePath,
	WritingVectors,
	WritingOrbitalParameters,
	// ManuallyAngularMeasurementsAndDates class
	EnteringAlpha1,
	EnteringDelta1,
	EnteringDate1,
	EnteringAlpha2,
	EnteringDelta2,
	EnteringDate2,
	EnteringAlpha3,
	EnteringDelta3,
	EnteringDate3,
	// ManuallyObservationPoints class
	ChoosingOneObservationPoint,
	EnteringPhi1,
	EnteringLambda1,
	EnteringH1,
	EnteringPhi2,
	EnteringLambda2,
	EnteringH2,
	EnteringPhi3,
	EnteringLambda3,
	EnteringH3,
	// GlobalButtons class
	Calculate,
	Clear
};

class Components : public QObject
{
protected:
	Ui::OrbitDeterminationAppClass* m_pOrbitDeterminationAppClass;
	Mediator* m_pMediator;
	QDoubleValidator* m_pDoubleValidator;
	QSettings m_componentsSettings;
public:
	Components(
		Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass = nullptr, 
		Mediator* aMediator = nullptr);
	~Components();
	void SetMediator(Mediator* aMediator);
};

