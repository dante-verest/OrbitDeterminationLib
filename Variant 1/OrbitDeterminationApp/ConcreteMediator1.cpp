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
			m_funcMethodFunction = Gauss;
			break;
		case ChoosingLaplasMethod:
			m_funcMethodFunction = Laplas;
			break;
		case ChoosingEscobalMethod:
			m_funcMethodFunction = Escobal;
			break;
		};
	}
	else if (sender == m_pObservationPoints)
	{
		switch (event)
		{
		case SettingConstObservationPoint:

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
			break;
		}
	}
	else if (sender == m_pAngularMeasurementsAndDate)
	{
		switch (event)
		{
		case SettingManually:
			m_pAngularMeasurementsAndDate->SetReadOnlyAllMeasurements(false);
			break;
		case SettingReadFromFile:
			
			break;
		case SettingReadFromTLEfile:
			
			break;
		case AddingTLEfilePath:
			m_strTLEfilePath = QFileDialog::getOpenFileName();
			break;
		}
	}
	else if (sender == m_pFileResults)
	{
		switch (event)
		{
		case AddingOutputFilePath:
			m_strOutputFilePath = QFileDialog::getOpenFileName();
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
			m_pOrbitDeterminationAppClass->columnsLabel->setEnabled(false);
			m_pOrbitDeterminationAppClass->firstColumnCheckBox->setEnabled(false);
			m_pOrbitDeterminationAppClass->secondColumnCheckBox->setEnabled(false);
			m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setEnabled(false);
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
			//if (!m_aAngularMeasurements.empty() && !m_aDates.empty() && !m_aPoints.empty())
			//{
			//	m_funcMethodFunction(m_aAngularMeasurements, m_aDates, m_aPoints, m_r_2, m_v_2, m_orbitalParameters);
			//	m_pOutputVectorsAndOrbitalParameters->SetResultsToLineEdits(m_r_2, m_v_2, m_orbitalParameters);
			//}
			//else
			{
				int index = m_pOrbitDeterminationAppClass->methodComboBox->currentIndex();
				switch (index)
				{
				case ChoosingGaussMethod:
					m_funcMethodFunction = Gauss;
					break;
				case ChoosingLaplasMethod:
					m_funcMethodFunction = Laplas;
					break;
				case ChoosingEscobalMethod:
					m_funcMethodFunction = Escobal;
					break;
				};
				m_aAngularMeasurements[0].alpha = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_1);
				m_aAngularMeasurements[1].alpha = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_2);
				m_aAngularMeasurements[2].alpha = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->alphaLineEdit_3);
				m_aAngularMeasurements[0].delta = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_1);
				m_aAngularMeasurements[1].delta = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_2);
				m_aAngularMeasurements[2].delta = m_pManuallyAngularMeasurementsAndDate->
					GetAngularMeasurement(*m_pOrbitDeterminationAppClass->deltaLineEdit_3);
				m_aDates[0] = m_pManuallyAngularMeasurementsAndDate->
					GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_1);
				m_aDates[1] = m_pManuallyAngularMeasurementsAndDate->
					GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_2);
				m_aDates[2] = m_pManuallyAngularMeasurementsAndDate->
					GetDate(*m_pOrbitDeterminationAppClass->dateTimeEdit_3);
				m_aPoints[0].phi = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_1);
				m_aPoints[1].phi = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_2);
				m_aPoints[2].phi = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->phiLineEdit_3);
				m_aPoints[0].lambda = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_1);
				m_aPoints[1].lambda = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_2);
				m_aPoints[2].lambda = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->lambdaLineEdit_3);
				m_aPoints[0].H = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_1);
				m_aPoints[1].H = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_2);
				m_aPoints[2].H = m_pManuallyObservationPoints->
					GetObservationPointsField(*m_pOrbitDeterminationAppClass->HlineEdit_3);
				m_funcMethodFunction(m_aAngularMeasurements, m_aDates, m_aPoints, m_r_2, m_v_2, m_orbitalParameters);
				m_pOutputVectorsAndOrbitalParameters->SetResultsToLineEdits(m_r_2, m_v_2, m_orbitalParameters);
			}
			break;
		case Clear:

			break;
		}
	}
};