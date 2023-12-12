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
	//connect(
	//	m_pOrbitDeterminationAppClass->filePathLineEdit,
	//	static_cast<void (QLineEdit::*)(bool)>(&QLineEdit::)
	//)
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
	m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setEnabled(m_componentsSettings.value("/enabled radius-vectors", false).toBool());
	m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setChecked(m_componentsSettings.value("/chosen radius-vectors", false).toBool());
	m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setEnabled(m_componentsSettings.value("/enabled orbital parameters", false).toBool());
	m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setChecked(m_componentsSettings.value("/chosen orbital parameters", false).toBool());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::FileResults::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for file results");

	m_componentsSettings.setValue("/file path", m_pOrbitDeterminationAppClass->filePathLineEdit->text());
	m_componentsSettings.setValue("/enabled radius-vectors", m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->isEnabled());
	m_componentsSettings.setValue("/chosen radius-vectors", m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->isChecked());
	m_componentsSettings.setValue("/enabled orbital parameters", m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->isEnabled());
	m_componentsSettings.setValue("/chosen orbital parameters", m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->isChecked());

	m_componentsSettings.endGroup();
};

//void FirstInputParameters::FileResults::IsWriteToFile(bool a_bChecked)
//{
//	this->m_pMediator->Notify(this, "");
//};

void FirstInputParameters::FileResults::WhatWriteToFile(bool& isVectors, bool& isOrbitalParameters)
{
	isVectors = m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->isChecked();
	isOrbitalParameters = m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->isChecked();
};

bool FirstInputParameters::FileResults::WriteResultsToFile(
	const char* methodName,
	const Vector3<double>& r_2,
	const Vector3<double>& v_2,
	const OrbitalParameters<double>& aOrbitalParameters)
{
	if (m_strOutputFilePath.isEmpty())
		m_strOutputFilePath = m_pOrbitDeterminationAppClass->filePathLineEdit->text();
	QFile m_toFile(m_strOutputFilePath);
	if (!m_toFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{
		QMessageBox::critical(m_pOrbitDeterminationAppClass->centralWidget, tr("Error"),
			QString("Unpossible to open file by path %1!").arg(m_strOutputFilePath));
		return false;
	}
	QTextStream out(&m_toFile);
	out << "Method: " << methodName << "\n";
	if (m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->isChecked())
	{
		out << "Radius-vectors:\n";
		QString r_2_string, v_2_string;
		static const char letters[3][2] = { "i", "j", "k" };
		for (std::size_t i = 0; i < 3; i++)
		{
			if (r_2[i] < 0)
				r_2_string += QString("%1").arg(r_2[i]);
			else
				r_2_string += QString("+%1").arg(r_2[i]);
			r_2_string += letters[i];
			if (v_2[i] < 0)
				v_2_string += QString("%1").arg(v_2[i]);
			else
				v_2_string += QString("+%1").arg(v_2[i]);
			v_2_string += letters[i];
		}
		out << "\tr_2:\t" << r_2_string << "\n\tv_2:\t" << v_2_string << "\n";
	}
	if (m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->isChecked())
	{
		out << "Orbital parameters:\n";
		out << "\tinclination = " << aOrbitalParameters.i.value() << " rad\n";
		out << "\tright ascention of the ascending node = " << aOrbitalParameters.Omega.value() << " rad\n";
		out << "\targument of perigee = " << aOrbitalParameters.omega.value() << " rad\n";
		out << "\teccentricity = " << aOrbitalParameters.e.value() << "\n";
		out << "\tlarge semi-axis = " << aOrbitalParameters.a.value() << " km\n";
		out << "\ttrue anomaly = " << aOrbitalParameters.Theta.value() << " rad\n";
		out << "\tangular momentum = " << aOrbitalParameters.h.value() << " km^2/s\n\n";
	}
	m_toFile.close();
	return true;
};

void FirstInputParameters::FileResults::ClearAll()
{
	m_pOrbitDeterminationAppClass->filePathLineEdit->clear();
	m_pOrbitDeterminationAppClass->filePathLineEdit->setEnabled(false);
	m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setChecked(false);
	m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setEnabled(false);
	m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setChecked(false);
	m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setEnabled(false);
};

void FirstInputParameters::FileResults::AddPath()
{
	//this->m_pMediator->Notify(this, Commands::AddingOutputFilePath);
	m_strOutputFilePath = QFileDialog::getSaveFileName(m_pOrbitDeterminationAppClass->centralWidget,
		tr("Open file"), tr("./"), tr("*.txt"));
	if (!m_strOutputFilePath.isEmpty())
	{
		m_pOrbitDeterminationAppClass->filePathLineEdit->setText(m_strOutputFilePath);
		m_pOrbitDeterminationAppClass->isSpeedAndDistanceCheckBox->setEnabled(true);
		m_pOrbitDeterminationAppClass->isOrbitParametersCheckBox->setEnabled(true);
	}
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