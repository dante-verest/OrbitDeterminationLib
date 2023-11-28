#include "stdafx.h"
#include "FileResults.h"

FirstInputParameters::FileResults::FileResults(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	this->ReadSettings();

	//connect(
	//	m_pOrbitDeterminationAppClass->fileResultsGroupBox,
	//	static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::toggled),
	//	m_pOrbitDeterminationAppClass->fileResultsGroupBox,
	//	static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::setEnabled));
	connect(
		m_pOrbitDeterminationAppClass->pathPushButton,
		&QPushButton::pressed,
		this,
		&FileResults::AddPath);
	connect(
		m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox,
		static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled),
		this,
		static_cast<void (FileResults::*)(bool)>(&FileResults::IsVectors));
	connect(
		m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox,
		static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::toggled),
		this,
		static_cast<void (FileResults::*)(bool)>(&FileResults::IsOrbitalParameters));
};

FirstInputParameters::FileResults::~FileResults()
{
	this->WriteSettings();
};

void FirstInputParameters::FileResults::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for file results");

	m_pOrbitDeterminationAppClass->filePathLineEdit->setText(m_componentsSettings.value("/file path", "").toString());
	m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setChecked(m_componentsSettings.value("/chosen radius-vectors", false).toBool());
	m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setChecked(m_componentsSettings.value("/chosen orbital parameters", false).toBool());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::FileResults::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for file results");

	m_componentsSettings.setValue("/file path", m_pOrbitDeterminationAppClass->filePathLineEdit->text());
	m_componentsSettings.setValue("/chosen radius-vectors", m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->isChecked());
	m_componentsSettings.setValue("/chosen orbital parameters", m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->isChecked());

	m_componentsSettings.endGroup();
};

//void FirstInputParameters::FileResults::IsWriteToFile(bool a_bChecked)
//{
//	this->m_pMediator->Notify(this, "");
//};

void FirstInputParameters::FileResults::AddPath()
{
	this->m_pMediator->Notify(this, Commands::AddingOutputFilePath);
};

void FirstInputParameters::FileResults::IsVectors(bool a_bChecked)
{
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::WritingVectors);
};

void FirstInputParameters::FileResults::IsOrbitalParameters(bool a_bChecked)
{
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::WritingOrbitalParameters);
};