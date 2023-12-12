#include "stdafx.h"
#include "ConcreteMediator1.h"

ConcreteMediator1::ConcreteMediator1(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass) :
	m_pOrbitDeterminationAppClass(aOrbitDeterminationAppClass)
{
	m_pAngularMeasurementsAndDate = new FirstInputParameters::
		AngularMeasurementsAndDate(aOrbitDeterminationAppClass, this);
	m_pFileResults = new FirstInputParameters::
		FileResults(aOrbitDeterminationAppClass, this);
	m_pMeasurementMethod = new FirstInputParameters::
		MeasurementMethod(aOrbitDeterminationAppClass, this);
	m_pObservationPoints = new FirstInputParameters::
		ObservationPoints(aOrbitDeterminationAppClass, this);
	m_pManuallyAngularMeasurementsAndDate = new SecondInputParameters::
		ManuallyAngularMeasurementsAndDate(aOrbitDeterminationAppClass, this);
	m_pManuallyObservationPoints = new SecondInputParameters::
		ManuallyObservationPoints(aOrbitDeterminationAppClass, this);
	m_pOutputVectorsAndOrbitalParameters = new Results::
		OutputVectorsAndOrbitalParameters(aOrbitDeterminationAppClass, this);
	m_pGlobalButtons = new Buttons::
		GlobalButtons(aOrbitDeterminationAppClass, this);
};

ConcreteMediator1::~ConcreteMediator1()
{
	delete m_pAngularMeasurementsAndDate;
	delete m_pFileResults;
	delete m_pMeasurementMethod;
	delete m_pObservationPoints;
	delete m_pManuallyAngularMeasurementsAndDate;
	delete m_pManuallyObservationPoints;
	delete m_pOutputVectorsAndOrbitalParameters;
	delete m_pGlobalButtons;
};

void ConcreteMediator1::Notify(Components* sender, Commands event)
{
	if (sender == m_pMeasurementMethod)
	{
		switch (event)
		{
		case ChoosingGaussMethod:
			m_methodName = "Gauss";
			break;
		case ChoosingLaplasMethod:
			m_methodName = "Laplas";
			break;
		case ChoosingEscobalMethod:
			m_methodName = "Escobal";
			break;
		};
	}
	else if (sender == m_pObservationPoints)
	{
		switch (event)
		{
		case SettingConstObservationPoint:
			m_pObservationPoints->SetReadOnlyAllColumns(true);
			m_bIsConstObservationPoint = true;
			m_bIsOwnObservationPoint = false;
			break;
		case ChoosingMinskPoint:
			//m_aPoints[0].phi = 
			//m_aPoints[0].lambda = 
			//m_aPoints[0].H = 
			break;
		case ChoosingFirstColumn:
			m_aChoosedColumn[0] = true;
			break;
		case ChoosingSecondColumn:
			m_aChoosedColumn[1] = true;
			break;
		case ChoosingThirdColumn:
			m_aChoosedColumn[2] = true;
			break;
		case AddingColumn:
			if (m_aChoosedColumn[0])
			{
				m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(QString::number(m_aPoints[0].phi));
				m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(QString::number(m_aPoints[0].lambda));
				m_pOrbitDeterminationAppClass->HlineEdit_1->setText(QString::number(m_aPoints[0].H));
			}
			if (m_aChoosedColumn[1])
			{
				m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(QString::number(m_aPoints[0].phi));
				m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(QString::number(m_aPoints[0].lambda));
				m_pOrbitDeterminationAppClass->HlineEdit_2->setText(QString::number(m_aPoints[0].H));
			}
			if (m_aChoosedColumn[2])
			{
				m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(QString::number(m_aPoints[0].phi));
				m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(QString::number(m_aPoints[0].lambda));
				m_pOrbitDeterminationAppClass->HlineEdit_3->setText(QString::number(m_aPoints[0].H));
			}
			break;
		case SettingOwnObservationPoint:
			m_pObservationPoints->SetReadOnlyAllColumns(false);
			m_bIsConstObservationPoint = false;
			m_bIsOwnObservationPoint = true;
			break;
		}
	}
	else if (sender == m_pAngularMeasurementsAndDate)
	{
		switch (event)
		{
		case SettingManually:
			m_pManuallyAngularMeasurementsAndDate->SetReadOnlyAllMeasurements(false);
			break;
		case SettingReadFromFile:
			m_pManuallyAngularMeasurementsAndDate->SetReadOnlyAllMeasurements(true);
			break;
		case SettingReadFromTLEfile:
			
			break;
		case AddingTLEfilePath:
			
			break;
		}
	}
	else if (sender == m_pFileResults)
	{
		switch (event)
		{
		case AddingOutputFilePath:
			
			break;
		case WritingVectors:

			break;
		case WritingOrbitalParameters:

			break;
		}
	}
	else if (sender == m_pManuallyAngularMeasurementsAndDate)
	{
		switch (event)
		{
		case EnteringAlpha1:
			m_aAngularMeasurements[0].alpha = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_1);
			break;
		case EnteringDelta1:
			m_aAngularMeasurements[0].delta = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_1);
			break;
		case EnteringDate1:
			m_aDates[0] = m_pManuallyAngularMeasurementsAndDate->
				GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_1);
			break;
		case EnteringAlpha2:
			m_aAngularMeasurements[1].alpha = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_2);
			break;
		case EnteringDelta2:
			m_aAngularMeasurements[1].delta = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_2);
			break;
		case EnteringDate2:
			m_aDates[1] = m_pManuallyAngularMeasurementsAndDate->
				GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_2);
			break;
		case EnteringAlpha3:
			m_aAngularMeasurements[2].alpha = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_3);
			break;
		case EnteringDelta3:
			m_aAngularMeasurements[2].delta = m_pManuallyAngularMeasurementsAndDate->
				GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_3);
			break;
		case EnteringDate3:
			m_aDates[2] = m_pManuallyAngularMeasurementsAndDate->
				GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_3);
			break;
		}
	}
	else if (sender == m_pManuallyObservationPoints)
	{
		switch (event)
		{
		case ChoosingOneObservationPoint:

			if (m_bIsConstObservationPoint)
				m_pObservationPoints->SetEnabledColumns(false);
			break;
		case ChoosingManyObservationPoints:

			if (m_bIsOwnObservationPoint)
				m_pObservationPoints->SetEnabledColumns(true);
			break;
		case EnteringPhi1:
			m_aPoints[0].phi = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_1);
			break;
		case EnteringLambda1:
			m_aPoints[0].lambda = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_1);
			break;
		case EnteringH1:
			m_aPoints[0].H = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_1);
			break;
		case EnteringPhi2:
			m_aPoints[1].phi = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_2);
			break;
		case EnteringLambda2:
			m_aPoints[1].lambda = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_2);
			break;
		case EnteringH2:
			m_aPoints[1].H = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_2);
			break;
		case EnteringPhi3:
			m_aPoints[2].phi = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_3);
			break;
		case EnteringLambda3:
			m_aPoints[2].lambda = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_2);
			break;
		case EnteringH3:
			m_aPoints[2].H = m_pManuallyObservationPoints->
				GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_3);
			break;
		}
	}
	else if (sender == m_pGlobalButtons)
	{
		switch (event)
		{
		case Calculate:
			if(m_methodName == "") m_methodName = m_pMeasurementMethod->GetCurrentItem().toStdString();
			if (m_pManuallyAngularMeasurementsAndDate->GetAngularMeasurementsAndDates(m_aAngularMeasurements, m_aDates) &&
				m_pManuallyObservationPoints->GetObservationPoints(m_aPoints))
				if (m_pGlobalButtons->Calculate(m_methodName.c_str(), m_aAngularMeasurements, m_aDates, m_aPoints,
					m_r_2, m_v_2, m_orbitalParameters, &m_calculateTime))
				{
					m_pOutputVectorsAndOrbitalParameters->SetResultsToLineEdits(m_methodName.c_str(), m_r_2, m_v_2, m_orbitalParameters);
					m_pFileResults->WriteResultsToFile(m_methodName.c_str(), m_r_2, m_v_2, m_orbitalParameters);
				}
			QApplication::beep();
			m_pOrbitDeterminationAppClass->statusBar->showMessage("Время рассчёта: " + 
				QString::number(m_calculateTime.count() * 1e-6) + " секунд.");
			break;
		case Clear:
			m_pAngularMeasurementsAndDate->ClearAll();
			//m_pObservationPoints->ClearAll();
			m_pFileResults->ClearAll();
			m_pManuallyAngularMeasurementsAndDate->ClearAll();
			m_pManuallyObservationPoints->ClearAll();
			m_pOutputVectorsAndOrbitalParameters->ClearAll();
			break;
		}
	}
};