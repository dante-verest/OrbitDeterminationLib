#include "stdafx.h"
#include "AngularMeasurementsAndDate.h"

FirstInputParameters::AngularMeasurementsAndDate::AngularMeasurementsAndDate(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	this->ReadSettings();

	connect(
		m_pOrbitDeterminationAppClass->manuallyRadioButton,
		static_cast<void (QAbstractButton::*)(bool)>(&QAbstractButton::toggled),
		this,
		static_cast<void (AngularMeasurementsAndDate::*)(bool)>(&AngularMeasurementsAndDate::Manually));
	connect(
		m_pOrbitDeterminationAppClass->fromFileRadioButton,
		static_cast<void (QAbstractButton::*)(bool)>(&QAbstractButton::toggled),
		this,
		static_cast<void (AngularMeasurementsAndDate::*)(bool)>(&AngularMeasurementsAndDate::FromFile));
	connect(
		m_pOrbitDeterminationAppClass->TLEradioButton,
		static_cast<void (QAbstractButton::*)(bool)>(&QAbstractButton::toggled),
		this,
		static_cast<void (AngularMeasurementsAndDate::*)(bool)>(&AngularMeasurementsAndDate::FromTLEfile));
	connect(
		m_pOrbitDeterminationAppClass->TLEfilePushButton,
		&QPushButton::pressed,
		this,
		&AngularMeasurementsAndDate::AddFilePath);
};

FirstInputParameters::AngularMeasurementsAndDate::~AngularMeasurementsAndDate()
{
	this->WriteSettings();
};

void FirstInputParameters::AngularMeasurementsAndDate::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for angular measurements and date");

	m_pOrbitDeterminationAppClass->manuallyRadioButton->setChecked(m_componentsSettings.value("/chosen manual entering", true).toBool());
	m_pOrbitDeterminationAppClass->fromFileRadioButton->setChecked(m_componentsSettings.value("/chosen data from file", false).toBool());
	m_pOrbitDeterminationAppClass->TLEradioButton->setChecked(m_componentsSettings.value("/chosen data from TLE file", false).toBool());
	m_pOrbitDeterminationAppClass->TLEfileLineEdit->setText(m_componentsSettings.value("/TLE file path", "").toString());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::AngularMeasurementsAndDate::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for angular measurements and date");

	m_componentsSettings.setValue("/chosen manual entering", m_pOrbitDeterminationAppClass->manuallyRadioButton->isChecked());
	m_componentsSettings.setValue("/chosen data from file", m_pOrbitDeterminationAppClass->fromFileRadioButton->isChecked());
	m_componentsSettings.setValue("/chosen data from TLE file", m_pOrbitDeterminationAppClass->TLEradioButton->isChecked());
	m_componentsSettings.setValue("/TLE file path", m_pOrbitDeterminationAppClass->TLEfileLineEdit->text());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::AngularMeasurementsAndDate::SetReadOnlyAllMeasurements(bool a_bOn)
{
	m_pOrbitDeterminationAppClass->alphaLineEdit_1->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->deltaLineEdit_1->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->dateTimeEdit_1->setReadOnly(a_bOn);

	m_pOrbitDeterminationAppClass->alphaLineEdit_2->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->deltaLineEdit_2->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->dateTimeEdit_2->setReadOnly(a_bOn);

	m_pOrbitDeterminationAppClass->alphaLineEdit_3->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->deltaLineEdit_3->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->dateTimeEdit_3->setReadOnly(a_bOn);
};

void FirstInputParameters::AngularMeasurementsAndDate::Manually(bool a_bChecked)
{
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::SettingManually);
};

void FirstInputParameters::AngularMeasurementsAndDate::FromFile(bool a_bChecked)
{
	m_pOrbitDeterminationAppClass->TLEradioButton->setEnabled(a_bChecked);
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::SettingReadFromFile);
};

void FirstInputParameters::AngularMeasurementsAndDate::FromTLEfile(bool a_bChecked)
{
	m_pOrbitDeterminationAppClass->TLEfilePushButton->setEnabled(a_bChecked);
	m_pOrbitDeterminationAppClass->TLEfileLineEdit->setEnabled(a_bChecked);
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::SettingReadFromTLEfile);
};

void FirstInputParameters::AngularMeasurementsAndDate::AddFilePath()
{
	this->m_pMediator->Notify(this, Commands::AddingTLEfilePath);
}