#include "stdafx.h"
#include "OutputVectorsAndOrbitalParameters.h"

Results::OutputVectorsAndOrbitalParameters::OutputVectorsAndOrbitalParameters(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->methodNameLineEdit->setReadOnly(true);
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

	m_pMethodName = m_componentsSettings.value("/method name", "").toString();
	m_pOrbitDeterminationAppClass->methodNameLineEdit->setText(m_pMethodName);

	QString str;
	QStringList list;
	str = m_componentsSettings.value("/r_2", "").toString();
	list = str.split(QRegularExpression("(i|j|k)"));
	m_r_2[0] = list.at(0).toDouble();
	m_r_2[1] = list.at(1).toDouble();
	m_r_2[2] = list.at(2).toDouble();
	m_pOrbitDeterminationAppClass->r_2LineEdit->setText(str);
	str = m_componentsSettings.value("/v_2", "").toString();
	list = str.split(QRegularExpression("(i|j|k)"));
	m_v_2[0] = list.at(0).toDouble();
	m_v_2[1] = list.at(1).toDouble();
	m_v_2[2] = list.at(2).toDouble();
	m_pOrbitDeterminationAppClass->v_2LineEdit->setText(str);

	m_orbitalParameters.i = m_componentsSettings.value("/inclination", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->inclinationLineEdit->setText(QString::number(m_orbitalParameters.i.value()));
	m_orbitalParameters.Omega = m_componentsSettings.value("/right ascention of the ascending node", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setText(QString::number(m_orbitalParameters.Omega.value()));
	m_orbitalParameters.omega = m_componentsSettings.value("/argument of perigee", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setText(QString::number(m_orbitalParameters.omega.value()));
	m_orbitalParameters.e = m_componentsSettings.value("/eccentricity", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setText(QString::number(m_orbitalParameters.e.value()));
	m_orbitalParameters.a = m_componentsSettings.value("/large semi-axis", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setText(QString::number(m_orbitalParameters.a.value()));
	m_orbitalParameters.Theta = m_componentsSettings.value("/true anomaly", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setText(QString::number(m_orbitalParameters.Theta.value()));
	m_orbitalParameters.h = m_componentsSettings.value("/angular momentum", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setText(QString::number(m_orbitalParameters.h.value()));

	m_componentsSettings.endGroup();
};

void Results::OutputVectorsAndOrbitalParameters::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for result output vectors and orbital parameters");

	m_componentsSettings.setValue("/method name", m_pOrbitDeterminationAppClass->methodNameLineEdit->text());

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


void Results::OutputVectorsAndOrbitalParameters::SetMethodName(const QString& aMethodName)
{
	this->m_pMethodName = aMethodName;
};

const QString& Results::OutputVectorsAndOrbitalParameters::GetMethodName()
{
	return this->m_pMethodName;
};

void Results::OutputVectorsAndOrbitalParameters::Set_r_2(const Vector3<double>& r_2)
{
	this->m_r_2 = r_2;
};

const Vector3<double>& Results::OutputVectorsAndOrbitalParameters::Get_r_2()
{
	return this->m_r_2;
};

void Results::OutputVectorsAndOrbitalParameters::Set_v_2(const Vector3<double>& v_2)
{
	this->m_v_2 = v_2;
};

const Vector3<double>& Results::OutputVectorsAndOrbitalParameters::Get_v_2()
{
	return this->m_v_2;
};

void Results::OutputVectorsAndOrbitalParameters::SetOrbitalParameters(const OrbitalParameters<double>& aOrbitalParameters)
{
	this->m_orbitalParameters = aOrbitalParameters;
};

const OrbitalParameters<double>& Results::OutputVectorsAndOrbitalParameters::GetOrbitalParameters()
{
	return this->m_orbitalParameters;
};

QString Results::OutputVectorsAndOrbitalParameters::FullFormOfVector(const Eigen::Vector3<double>& vector)
{
	//QString strVector;
	//static const char letters[3][2] = { "i", "j", "k" };
	//for (std::size_t i = 0; i < 3; i++)
	//{
	//	if (vector[i] < 0)
	//		strVector += QString("%1").arg(vector[i]);
	//	else
	//		strVector += QString("+%1").arg(vector[i]);
	//	strVector += letters[i];
	//}
	//return /*std::move*/(strVector);
	return QString("%1i%2j%3k").
		arg(QString::number(vector[0])).
		arg(vector[1] < 0 ? QString::number(vector[1]) : ("+" + QString::number(vector[1]))).
		arg(vector[2] < 0 ? QString::number(vector[2]) : ("+" + QString::number(vector[2])));
};

void Results::OutputVectorsAndOrbitalParameters::SetResultsToLineEdits()
{
	m_pOrbitDeterminationAppClass->methodNameLineEdit->setText(m_pMethodName);
	m_pOrbitDeterminationAppClass->r_2LineEdit->setText(this->FullFormOfVector(m_r_2));
	m_pOrbitDeterminationAppClass->v_2LineEdit->setText(this->FullFormOfVector(m_v_2));
	m_pOrbitDeterminationAppClass->inclinationLineEdit->setText(QString::number(m_orbitalParameters.i.value()));
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setText(QString::number(m_orbitalParameters.Omega.value()));
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setText(QString::number(m_orbitalParameters.omega.value()));
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setText(QString::number(m_orbitalParameters.e.value()));
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setText(QString::number(m_orbitalParameters.a.value()));
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setText(QString::number(m_orbitalParameters.Theta.value()));
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setText(QString::number(m_orbitalParameters.h.value()));
};

Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters*
Results::OutputVectorsAndOrbitalParameters::Save()
{
	return new Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters(
		m_pOrbitDeterminationAppClass->methodNameLineEdit->text(),
		m_pOrbitDeterminationAppClass->r_2LineEdit->text(),
		m_pOrbitDeterminationAppClass->v_2LineEdit->text(),
		m_pOrbitDeterminationAppClass->inclinationLineEdit->text(),
		m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->text(),
		m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->text(),
		m_pOrbitDeterminationAppClass->eccentricityLineEdit->text(),
		m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->text(),
		m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->text(),
		m_pOrbitDeterminationAppClass->angularMomentumLineEdit->text());
};

void Results::OutputVectorsAndOrbitalParameters::Restore(
	Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters* memento)
{
	m_pOrbitDeterminationAppClass->methodNameLineEdit->setText(memento->GetMethodName());
	m_pOrbitDeterminationAppClass->r_2LineEdit->setText(memento->Get_r_2());
	m_pOrbitDeterminationAppClass->v_2LineEdit->setText(memento->Get_v_2());
	m_pOrbitDeterminationAppClass->inclinationLineEdit->setText(memento->GetInclination());
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->setText(memento->GetRightAscentionOfTheAscendingNode());
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->setText(memento->GetArgumentOfPerigee());
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->setText(memento->GetEccentricity());
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->setText(memento->GetLargeSemiaxis());
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->setText(memento->GetTrueAnomaly());
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->setText(memento->GetAngularMomentum());
};

void Results::OutputVectorsAndOrbitalParameters::ClearAll()
{
	m_pOrbitDeterminationAppClass->methodNameLineEdit->clear();
	m_pOrbitDeterminationAppClass->r_2LineEdit->clear();
	m_pOrbitDeterminationAppClass->v_2LineEdit->clear();
	m_pOrbitDeterminationAppClass->inclinationLineEdit->clear();
	m_pOrbitDeterminationAppClass->rightAscentionOfTheAscendingNodeLineEdit->clear();
	m_pOrbitDeterminationAppClass->argumentOfPerigeeLineEdit->clear();
	m_pOrbitDeterminationAppClass->eccentricityLineEdit->clear();
	m_pOrbitDeterminationAppClass->largeSemiaxisLineEdit->clear();
	m_pOrbitDeterminationAppClass->trueAnomalyLineEdit->clear();
	m_pOrbitDeterminationAppClass->angularMomentumLineEdit->clear();
};