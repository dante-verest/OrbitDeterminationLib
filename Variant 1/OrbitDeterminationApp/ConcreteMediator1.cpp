#include "stdafx.h"
#include "ConcreteMediator1.h"

ConcreteMediator1::ConcreteMediator1(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass)/* :
	m_pOrbitDeterminationAppClass(aOrbitDeterminationAppClass)*/
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
	m_pMenu = new Menu::
		Menu(aOrbitDeterminationAppClass, this);
	m_pStatusBar = new StatusBar::
		StatusBar(aOrbitDeterminationAppClass, this);
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
	delete m_pMenu;
	delete m_pStatusBar;
};

void ConcreteMediator1::Notify(Components* sender, Commands event)
{
	if (sender == m_pMeasurementMethod)
	{
		switch (event)
		{
		};
	}
	else if (sender == m_pObservationPoints)
	{
		switch (event)
		{
		case SettingConstObservationPoint:
			if (m_pManuallyObservationPoints->IsOneObservationPoint())
			{
				m_pObservationPoints->SetEnabledComboBoxAndButton(true);
				m_pObservationPoints->SetEnabledAllCheckBoxes(false);
			}
			else
			{
				m_pObservationPoints->SetEnabledComboBoxAndButton(true);
				m_pObservationPoints->SetEnabledAllCheckBoxes(true);
			}
			m_pManuallyObservationPoints->SetReadOnlyAllColumns(true);
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(0, m_pObservationPoints->IsFirstColumn());
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(1, m_pObservationPoints->IsSecondColumn());
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(2, m_pObservationPoints->IsThirdColumn());
			break;
		case ChoosingFirstColumn:
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(0, m_pObservationPoints->IsFirstColumn());
			break;
		case ChoosingSecondColumn:
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(1, m_pObservationPoints->IsSecondColumn());
			break;
		case ChoosingThirdColumn:
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(2, m_pObservationPoints->IsThirdColumn());
			break;
		case AddingColumn:
			if (m_pObservationPoints->IsFirstColumn())
			{
				m_pManuallyObservationPoints->SetObservationPointToColumn(0, m_pObservationPoints->GetObservationPoint());
				m_pManuallyObservationPoints->SetHighlightedBorderToColumn(0, false);
			}
			if (m_pObservationPoints->IsSecondColumn())
			{
				m_pManuallyObservationPoints->SetObservationPointToColumn(1, m_pObservationPoints->GetObservationPoint());
				m_pManuallyObservationPoints->SetHighlightedBorderToColumn(1, false);
			}
			if (m_pObservationPoints->IsThirdColumn())
			{
				m_pManuallyObservationPoints->SetObservationPointToColumn(2, m_pObservationPoints->GetObservationPoint());
				m_pManuallyObservationPoints->SetHighlightedBorderToColumn(2, false);
			}
			if (m_pManuallyObservationPoints->IsOneObservationPoint())
				m_pManuallyObservationPoints->SetObservationPointToColumn(0, m_pObservationPoints->GetObservationPoint());
			break;
		case SettingOwnObservationPoint:
			m_pManuallyObservationPoints->SetReadOnlyAllColumns(false);
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(0, false);
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(1, false);
			m_pManuallyObservationPoints->SetHighlightedBorderToColumn(2, false);
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
		//case SettingReadFromTLEfile:
		//	
		//	break;
		case AddingTLEfilePath:
			
			break;
		}
	}
	else if (sender == m_pFileResults)
	{
		switch (event)
		{
		}
	}
	else if (sender == m_pManuallyAngularMeasurementsAndDate)
	{
		switch (event)
		{
		}
	}
	else if (sender == m_pManuallyObservationPoints)
	{
		switch (event)
		{
		case ChoosingOneObservationPoint:
			if (m_pObservationPoints->IsConstObservationPoint())
				m_pObservationPoints->SetEnabledAllCheckBoxes(!m_pManuallyObservationPoints->IsOneObservationPoint());
			break;
		}
	}
	else if (sender == m_pGlobalButtons)
	{
		switch (event)
		{
		case Calculate:
			if (m_pGlobalButtons->Calculate(
				m_pMeasurementMethod->GetCurrentItem(), 
				m_pManuallyAngularMeasurementsAndDate->GetAngularMeasurements(), 
				m_pManuallyAngularMeasurementsAndDate->GetDates(), 
				m_pManuallyObservationPoints->GetObservationPoints(),
				m_pMenu->IsDebug()))
			{
				m_pOutputVectorsAndOrbitalParameters->SetMethodName(m_pMeasurementMethod->GetCurrentItem());
				m_pOutputVectorsAndOrbitalParameters->Set_r_2(m_pGlobalButtons->Get_r_2());
				m_pOutputVectorsAndOrbitalParameters->Set_v_2(m_pGlobalButtons->Get_v_2());
				m_pOutputVectorsAndOrbitalParameters->SetOrbitalParameters(m_pGlobalButtons->GetOrbitalParameters());
				m_pOutputVectorsAndOrbitalParameters->SetResultsToLineEdits();
				m_pFileResults->WriteResultsToFile(
					m_pMeasurementMethod->GetCurrentItem(), 
					m_pOutputVectorsAndOrbitalParameters->Get_r_2(), 
					m_pOutputVectorsAndOrbitalParameters->Get_v_2(), 
					m_pOutputVectorsAndOrbitalParameters->GetOrbitalParameters());
			}
			QApplication::beep();
			m_pStatusBar->AddMessage("Время рассчёта: " +
				QString::number(m_pGlobalButtons->GetCalculationTime().count() * 1e-6) + " секунд.");
			break;
		case Clear:
			m_pAngularMeasurementsAndDate->ClearAll();
			//m_pObservationPoints->ClearAll();
			m_pFileResults->ClearAll();
			m_pManuallyAngularMeasurementsAndDate->ClearAll();
			m_pManuallyObservationPoints->ClearAll();
			m_pOutputVectorsAndOrbitalParameters->ClearAll();
			m_pStatusBar->Clear();
			break;
		}
	}
	else if (sender == m_pMenu)
	{
		switch (event)
		{
		}
	}
};