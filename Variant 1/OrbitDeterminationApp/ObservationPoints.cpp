#include "stdafx.h"
#include "ObservationPoints.h"

FirstInputParameters::ObservationPoints::ObservationPoints(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->observationPointComboBox->addItem(m_observationPointsNames.at(0));
	m_pOrbitDeterminationAppClass->observationPointComboBox->addItem(m_observationPointsNames.at(1));

	this->ReadSettings();

	connect(
		m_pOrbitDeterminationAppClass->observationPointRadioButton,
		static_cast<void (QRadioButton::*)(bool)>(&QRadioButton::toggled),
		this,
		static_cast<void (ObservationPoints::*)(bool)>(&ObservationPoints::IsConstObservationPoints));
	//connect(
	//	m_pOrbitDeterminationAppClass->observationPointComboBox,
	//	static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
	//	this,
	//	static_cast<void (ObservationPoints::*)(int)>(&ObservationPoints::Items));
	connect(
		m_pOrbitDeterminationAppClass->firstColumnCheckBox,
		static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled),
		this,
		static_cast<void (ObservationPoints::*)(bool)>(&ObservationPoints::FirstColumn));
	connect(
		m_pOrbitDeterminationAppClass->secondColumnCheckBox,
		static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled),
		this,
		static_cast<void (ObservationPoints::*)(bool)>(&ObservationPoints::SecondColumn));
	connect(
		m_pOrbitDeterminationAppClass->thirdColumnCheckBox,
		static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled),
		this,
		static_cast<void (ObservationPoints::*)(bool)>(&ObservationPoints::ThirdColumn));
	connect(
		m_pOrbitDeterminationAppClass->addConstObservationPointPushButton,
		&QPushButton::pressed,
		this,
		&ObservationPoints::AddColumn);
	connect(
		m_pOrbitDeterminationAppClass->manuallyObservationPointRadioButton,
		static_cast<void (QRadioButton::*)(bool)>(&QRadioButton::toggled),
		this,
		static_cast<void (ObservationPoints::*)(bool)>(&ObservationPoints::IsOwnObservationPoints));
};

FirstInputParameters::ObservationPoints::~ObservationPoints()
{
	this->WriteSettings();
};

void FirstInputParameters::ObservationPoints::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for observation points");

	m_pOrbitDeterminationAppClass->observationPointRadioButton->setChecked(m_componentsSettings.value("/chosen const observation point", false).toBool());
	m_pOrbitDeterminationAppClass->observationPointComboBox->setEnabled(m_componentsSettings.value("/enabled list of const observation points", true).toBool());
	m_pOrbitDeterminationAppClass->observationPointComboBox->setCurrentIndex(m_componentsSettings.value("/observation point", 0).toInt());
	m_pOrbitDeterminationAppClass->columnsLabel->setEnabled(m_componentsSettings.value("/enabled column\'s label", true).toBool());
	m_pOrbitDeterminationAppClass->firstColumnCheckBox->setEnabled(m_componentsSettings.value("/enabled first column", true).toBool());
	m_pOrbitDeterminationAppClass->firstColumnCheckBox->setChecked(m_componentsSettings.value("/chosen first column", false).toBool());
	m_pOrbitDeterminationAppClass->secondColumnCheckBox->setEnabled(m_componentsSettings.value("/enabled second column", true).toBool());
	m_pOrbitDeterminationAppClass->secondColumnCheckBox->setChecked(m_componentsSettings.value("/chosen second column", false).toBool());
	m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setEnabled(m_componentsSettings.value("/enabled third column", true).toBool());
	m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setChecked(m_componentsSettings.value("/chosen third column", false).toBool());
	m_pOrbitDeterminationAppClass->addConstObservationPointPushButton->setEnabled(m_componentsSettings.value("/enabled add button", true).toBool());

	m_pOrbitDeterminationAppClass->manuallyObservationPointRadioButton->setChecked(m_componentsSettings.value("/chosen manual observation point", true).toBool());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::ObservationPoints::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for observation points");

	m_componentsSettings.setValue("/chosen const observation point", m_pOrbitDeterminationAppClass->observationPointRadioButton->isChecked());
	m_componentsSettings.setValue("/enabled list of const observation points", m_pOrbitDeterminationAppClass->observationPointComboBox->isEnabled());
	m_componentsSettings.setValue("/observation point", m_pOrbitDeterminationAppClass->observationPointComboBox->currentIndex());
	m_componentsSettings.setValue("/enabled column\'s label", m_pOrbitDeterminationAppClass->columnsLabel->isEnabled());
	m_componentsSettings.setValue("/enabled first column", m_pOrbitDeterminationAppClass->firstColumnCheckBox->isEnabled());
	m_componentsSettings.setValue("/chosen first column", m_pOrbitDeterminationAppClass->firstColumnCheckBox->isChecked());
	m_componentsSettings.setValue("/enabled second column", m_pOrbitDeterminationAppClass->secondColumnCheckBox->isEnabled());
	m_componentsSettings.setValue("/chosen second column", m_pOrbitDeterminationAppClass->secondColumnCheckBox->isChecked());
	m_componentsSettings.setValue("/enabled third column", m_pOrbitDeterminationAppClass->thirdColumnCheckBox->isEnabled());
	m_componentsSettings.setValue("/chosen third column", m_pOrbitDeterminationAppClass->thirdColumnCheckBox->isChecked());
	m_componentsSettings.setValue("/enabled add button", m_pOrbitDeterminationAppClass->addConstObservationPointPushButton->isEnabled());

	m_componentsSettings.setValue("/chosen manual observation point", m_pOrbitDeterminationAppClass->manuallyObservationPointRadioButton->isChecked());

	m_componentsSettings.endGroup();
};

ObservationPoint<double>&& FirstInputParameters::ObservationPoints::GetObservationPoint()
{
	ObservationPoint<double> observationPoint;
	switch (m_pOrbitDeterminationAppClass->observationPointComboBox->currentIndex())
	{
	case 0:
		observationPoint = m_observationPointsParameters.at(0);
		break;
	case 1:
		observationPoint = m_observationPointsParameters.at(1);
		break;
	}
	return std::move(observationPoint);
};

bool FirstInputParameters::ObservationPoints::IsConstObservationPoint()
{
	return m_pOrbitDeterminationAppClass->observationPointRadioButton->isChecked();
};

bool FirstInputParameters::ObservationPoints::IsFirstColumn()
{
	return m_pOrbitDeterminationAppClass->firstColumnCheckBox->isChecked();
};

bool FirstInputParameters::ObservationPoints::IsSecondColumn()
{
	return m_pOrbitDeterminationAppClass->secondColumnCheckBox->isChecked();
};

bool FirstInputParameters::ObservationPoints::IsThirdColumn()
{
	return m_pOrbitDeterminationAppClass->thirdColumnCheckBox->isChecked();
};

bool FirstInputParameters::ObservationPoints::IsManualObservationPoint()
{
	return m_pOrbitDeterminationAppClass->manuallyObservationPointRadioButton->isChecked();
};

void FirstInputParameters::ObservationPoints::SetCheckedAllCheckBoxes(bool a_bOn)
{
	m_pOrbitDeterminationAppClass->firstColumnCheckBox->setChecked(a_bOn);
	m_pOrbitDeterminationAppClass->secondColumnCheckBox->setChecked(a_bOn);
	m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setChecked(a_bOn);
};

void FirstInputParameters::ObservationPoints::SetEnabledAllCheckBoxes(bool bOn)
{
	m_pOrbitDeterminationAppClass->columnsLabel->setEnabled(bOn);
	m_pOrbitDeterminationAppClass->firstColumnCheckBox->setEnabled(bOn);
	m_pOrbitDeterminationAppClass->secondColumnCheckBox->setEnabled(bOn);
	m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setEnabled(bOn);
};

void FirstInputParameters::ObservationPoints::SetEnabledComboBoxAndButton(bool bOn)
{
	m_pOrbitDeterminationAppClass->observationPointComboBox->setEnabled(bOn);
	m_pOrbitDeterminationAppClass->addConstObservationPointPushButton->setEnabled(bOn);
};

//void FirstInputParameters::ObservationPoints::ClearAll()
//{
//
//};

void FirstInputParameters::ObservationPoints::IsConstObservationPoints(bool a_bChecked)
{
	//m_pOrbitDeterminationAppClass->observationPointComboBox->setEnabled(a_bChecked);
	//m_pOrbitDeterminationAppClass->columnsLabel->setEnabled(a_bChecked);
	//m_pOrbitDeterminationAppClass->firstColumnCheckBox->setEnabled(a_bChecked);
	//m_pOrbitDeterminationAppClass->secondColumnCheckBox->setEnabled(a_bChecked);
	//m_pOrbitDeterminationAppClass->thirdColumnCheckBox->setEnabled(a_bChecked);
	//m_pOrbitDeterminationAppClass->addConstObservationPointPushButton->setEnabled(a_bChecked);
	this->m_pMediator->Notify(this, Commands::SettingConstObservationPoint);
};

//void FirstInputParameters::ObservationPoints::Items(int a_nIndex)
//{
//	switch (a_nIndex)
//	{
//	case 0:
//		this->m_pMediator->Notify(this, Commands::ChoosingMinskPoint);
//		break;
//	}
//};

void FirstInputParameters::ObservationPoints::FirstColumn(bool a_bChecked)
{
	this->m_pMediator->Notify(this, Commands::ChoosingFirstColumn);
};

void FirstInputParameters::ObservationPoints::SecondColumn(bool a_bChecked)
{
	this->m_pMediator->Notify(this, Commands::ChoosingSecondColumn);
};

void FirstInputParameters::ObservationPoints::ThirdColumn(bool a_bChecked)
{
	this->m_pMediator->Notify(this, Commands::ChoosingThirdColumn);
};

void FirstInputParameters::ObservationPoints::AddColumn()
{
	this->m_pMediator->Notify(this, Commands::AddingColumn);
	this->SetCheckedAllCheckBoxes(false);
};

void FirstInputParameters::ObservationPoints::IsOwnObservationPoints(bool a_bChecked)
{
	this->SetEnabledComboBoxAndButton(!a_bChecked);
	this->SetEnabledAllCheckBoxes(!a_bChecked);
	this->m_pMediator->Notify(this, Commands::SettingOwnObservationPoint);
};