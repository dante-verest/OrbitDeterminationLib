#include "stdafx.h"
#include "ManuallyObservationPoints.h"

SecondInputParameters::ManuallyObservationPoints::ManuallyObservationPoints(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->phiLineEdit_1->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->HlineEdit_1->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->phiLineEdit_2->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->HlineEdit_2->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->phiLineEdit_3->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->HlineEdit_3->setValidator(m_pDoubleValidator);

	this->ReadSettings();

	connect(
		m_pOrbitDeterminationAppClass->oneObservationPointRadioButton,
		static_cast<void (QRadioButton::*)(bool)>(&QRadioButton::toggled),
		this,
		static_cast<void (ManuallyObservationPoints::*)(bool)>(&ManuallyObservationPoints::IsOneObservationPoint));
	// first column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetPhi1);
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetLambda1);
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetH1);
	// second column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetPhi2);
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetLambda2);
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetH2);
	// third column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetPhi3);
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetLambda3);
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyObservationPoints::SetH3);
};

SecondInputParameters::ManuallyObservationPoints::~ManuallyObservationPoints()
{
	this->WriteSettings();
};

void SecondInputParameters::ManuallyObservationPoints::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually observation points");

	m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(m_componentsSettings.value("/phi 1", "").toString());
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(m_componentsSettings.value("/lambda 1", "").toString());
	m_pOrbitDeterminationAppClass->HlineEdit_1->setText(m_componentsSettings.value("/H 1", "").toString());

	m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(m_componentsSettings.value("/phi 2", "").toString());
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(m_componentsSettings.value("/lambda 2", "").toString());
	m_pOrbitDeterminationAppClass->HlineEdit_2->setText(m_componentsSettings.value("/H 2", "").toString());

	m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(m_componentsSettings.value("/phi 3", "").toString());
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(m_componentsSettings.value("/lambda 3", "").toString());
	m_pOrbitDeterminationAppClass->HlineEdit_3->setText(m_componentsSettings.value("/H 3", "").toString());

	m_componentsSettings.endGroup();
};

void SecondInputParameters::ManuallyObservationPoints::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually observation points");

	m_componentsSettings.setValue("/phi 1", m_pOrbitDeterminationAppClass->phiLineEdit_1->text());
	m_componentsSettings.setValue("/lambda 1", m_pOrbitDeterminationAppClass->lambdaLineEdit_1->text());
	m_componentsSettings.setValue("/H 1", m_pOrbitDeterminationAppClass->HlineEdit_1->text());

	m_componentsSettings.setValue("/phi 2", m_pOrbitDeterminationAppClass->phiLineEdit_2->text());
	m_componentsSettings.setValue("/lambda 2", m_pOrbitDeterminationAppClass->lambdaLineEdit_2->text());
	m_componentsSettings.setValue("/H 2", m_pOrbitDeterminationAppClass->HlineEdit_2->text());

	m_componentsSettings.setValue("/phi 3", m_pOrbitDeterminationAppClass->phiLineEdit_3->text());
	m_componentsSettings.setValue("/lambda 3", m_pOrbitDeterminationAppClass->lambdaLineEdit_3->text());
	m_componentsSettings.setValue("/H 3", m_pOrbitDeterminationAppClass->HlineEdit_3->text());

	m_componentsSettings.endGroup();
};

double SecondInputParameters::ManuallyObservationPoints::GetObservationPointsField(const QLineEdit& lineEdit)
{
	return lineEdit.text().toDouble();
};

void SecondInputParameters::ManuallyObservationPoints::IsOneObservationPoint(bool a_bChecked)
{
	if (a_bChecked)
		this->m_pMediator->Notify(this, Commands::ChoosingOneObservationPoint);
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi1()
{
	this->m_pMediator->Notify(this, Commands::EnteringPhi1);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda1()
{
	this->m_pMediator->Notify(this, Commands::EnteringLambda1);
};

void SecondInputParameters::ManuallyObservationPoints::SetH1()
{
	this->m_pMediator->Notify(this, Commands::EnteringH1);
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi2()
{
	this->m_pMediator->Notify(this, Commands::EnteringPhi2);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda2()
{
	this->m_pMediator->Notify(this, Commands::EnteringLambda2);
};

void SecondInputParameters::ManuallyObservationPoints::SetH2()
{
	this->m_pMediator->Notify(this, Commands::EnteringH2);
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi3()
{
	this->m_pMediator->Notify(this, Commands::EnteringPhi3);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda3()
{
	this->m_pMediator->Notify(this, Commands::EnteringLambda3);
};

void SecondInputParameters::ManuallyObservationPoints::SetH3()
{
	this->m_pMediator->Notify(this, Commands::EnteringH3);
};