#include "stdafx.h"
#include "OutputVectorsAndOrbitalParameters.h"

Results::OutputVectorsAndOrbitalParameters::OutputVectorsAndOrbitalParameters(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->r_2LineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->v_2LineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->inclinationLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setReadOnly(true);
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setReadOnly(true);

	this->ReadSettings();
};

Results::OutputVectorsAndOrbitalParameters::~OutputVectorsAndOrbitalParameters()
{
	this->WriteSettings();
};

void Results::OutputVectorsAndOrbitalParameters::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for result output vectors and orbital parameters");

	m_pOrbitDeterminationAppClass->r_2LineEdit->setText(m_componentsSettings.value("/r_2", "").toString());
	m_pOrbitDeterminationAppClass->v_2LineEdit->setText(m_componentsSettings.value("/v_2", "").toString());

	m_pOrbitDeterminationAppClass->inclinationLineEdit->setText(m_componentsSettings.value("/inclination", "").toString());
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setText(m_componentsSettings.value("/right ascention of the ascending node", "").toString());
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setText(m_componentsSettings.value("/argument of perigee", "").toString());
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setText(m_componentsSettings.value("/eccentricity", "").toString());
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setText(m_componentsSettings.value("/large semi-axis", "").toString());
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setText(m_componentsSettings.value("/true anomaly", "").toString());
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setText(m_componentsSettings.value("/angular momentum", "").toString());

	m_componentsSettings.endGroup();
};

void Results::OutputVectorsAndOrbitalParameters::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for result output vectors and orbital parameters");

	m_componentsSettings.setValue("/r_2", m_pOrbitDeterminationAppClass->r_2LineEdit->text());
	m_componentsSettings.setValue("/v_2", m_pOrbitDeterminationAppClass->v_2LineEdit->text());

	m_componentsSettings.setValue("/inclination", m_pOrbitDeterminationAppClass->inclinationLineEdit->text());
	m_componentsSettings.setValue("/right ascention of the ascending node", m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->text());
	m_componentsSettings.setValue("/argument of perigee", m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->text());
	m_componentsSettings.setValue("/eccentricity", m_pOrbitDeterminationAppClass->eccentricityLineEdit->text());
	m_componentsSettings.setValue("/large semi-axis", m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->text());
	m_componentsSettings.setValue("/true anomaly", m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->text());
	m_componentsSettings.setValue("/angular momentum", m_pOrbitDeterminationAppClass->angularMomentumLineEdit->text());

	m_componentsSettings.endGroup();
};

QString Results::OutputVectorsAndOrbitalParameters::FullFormOfVector(const Eigen::Vector3<double>& vector)
{
	QString strVector;
	static const char letters[3][2] = { "i", "j", "k" };
	for (std::size_t i = 0; i < 3; i++)
	{
		if (vector[i] < 0)
			strVector += QString("%1").arg(vector[i]);
		else
			strVector += QString("+%1").arg(vector[i]);
		strVector += letters[i];
	}
	return /*std::move*/(strVector);
};

void Results::OutputVectorsAndOrbitalParameters::SetResultsToLineEdits(
	const Eigen::Vector3<double>& r_2,
	const Eigen::Vector3<double>& v_2,
	const Structures::OrbitalParameters<double>& orbitalParameters)
{
	m_pOrbitDeterminationAppClass->r_2LineEdit->setText(this->FullFormOfVector(r_2));
	m_pOrbitDeterminationAppClass->v_2LineEdit->setText(this->FullFormOfVector(v_2));
	m_pOrbitDeterminationAppClass->inclinationLineEdit->setText(QString::number(orbitalParameters.i));
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setText(QString::number(orbitalParameters.Omega));
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setText(QString::number(orbitalParameters.omega));
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setText(QString::number(orbitalParameters.e));
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setText(QString::number(orbitalParameters.a));
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setText(QString::number(orbitalParameters.Theta));
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setText(QString::number(orbitalParameters.h));
};