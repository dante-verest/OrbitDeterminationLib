#include "stdafx.h"
#include "ManuallyObservationPoints.h"

SecondInputParameters::ManuallyObservationPoints::ManuallyObservationPoints(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pObservationPointsLineEdits = { {
		{m_pOrbitDeterminationAppClass->phiLineEdit_1,
			m_pOrbitDeterminationAppClass->phiLineEdit_2,
			m_pOrbitDeterminationAppClass->phiLineEdit_3},
		{m_pOrbitDeterminationAppClass->lambdaLineEdit_1,
			m_pOrbitDeterminationAppClass->lambdaLineEdit_2,
			m_pOrbitDeterminationAppClass->lambdaLineEdit_3},
		{m_pOrbitDeterminationAppClass->HlineEdit_1,
			m_pOrbitDeterminationAppClass->HlineEdit_2,
			m_pOrbitDeterminationAppClass->HlineEdit_3} } };

	connect(
		m_pOrbitDeterminationAppClass->oneObservationPointRadioButton,
		static_cast<void (QRadioButton::*)(bool)>(&QRadioButton::toggled),
		this,
		static_cast<void (ManuallyObservationPoints::*)(bool)>(&ManuallyObservationPoints::IsOneObservationPoint));

	//m_pOrbitDeterminationAppClass->phiLineEdit_1->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->HlineEdit_1->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->phiLineEdit_2->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->HlineEdit_2->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->phiLineEdit_3->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setValidator(m_pDoubleValidator);
	//m_pOrbitDeterminationAppClass->HlineEdit_3->setValidator(m_pDoubleValidator);

	this->ReadSettings();

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

	for (const auto& row : m_pObservationPointsLineEdits)
		for (const auto& col : row)
		{
			col->setValidator(m_pDoubleValidator);
			connect(
				this,
				static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changeTextSignal),
				col,
				static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::setText));
		}
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

double SecondInputParameters::ManuallyObservationPoints::GetObservationPointsField(
	const QLineEdit& lineEdit, bool* bOk)
{
	return lineEdit.text().toDouble(bOk);
};

bool SecondInputParameters::ManuallyObservationPoints::GetObservationPoints(
	std::array<ObservationPoint<double>, 3>& aPoints)
{
	aPoints[0].phi = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->phiLineEdit_1, &m_bOk[0]);
	aPoints[0].lambda = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->lambdaLineEdit_1, &m_bOk[1]);
	aPoints[0].H = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->HlineEdit_1, &m_bOk[2]);
	aPoints[1].phi = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->phiLineEdit_2, &m_bOk[3]);
	aPoints[1].lambda = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->lambdaLineEdit_2, &m_bOk[4]);
	aPoints[1].H = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->HlineEdit_2, &m_bOk[5]);
	aPoints[2].phi = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->phiLineEdit_3, &m_bOk[6]);
	aPoints[2].lambda = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->lambdaLineEdit_3, &m_bOk[7]);
	aPoints[2].H = this->GetObservationPointsField(
		*m_pOrbitDeterminationAppClass->HlineEdit_3, &m_bOk[8]);
	if (std::all_of(m_bOk.begin(), m_bOk.end(), [](const bool& bOk) {
		return bOk == true;
		}))
		return true;
	else
		return false;
};

void SecondInputParameters::ManuallyObservationPoints::ClearAll()
{
	m_pOrbitDeterminationAppClass->phiLineEdit_1->clear();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->clear();
	m_pOrbitDeterminationAppClass->HlineEdit_1->clear();

	m_pOrbitDeterminationAppClass->phiLineEdit_2->clear();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->clear();
	m_pOrbitDeterminationAppClass->HlineEdit_2->clear();

	m_pOrbitDeterminationAppClass->phiLineEdit_3->clear();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->clear();
	m_pOrbitDeterminationAppClass->HlineEdit_3->clear();
};

void SecondInputParameters::ManuallyObservationPoints::IsOneObservationPoint(bool a_bChecked)
{
	//static std::array<QLineEdit*, 3>::iterator activeRowOfLineEdits;
	if (a_bChecked)
	{
		//for (auto row = m_pObservationPointsLineEdits.begin(); row != m_pObservationPointsLineEdits.end(); ++row)
		//{
		//	activeRowOfLineEdits = std::find_if(row->begin(), row->end(),
		//		[](const QLineEdit* rowLineEdits) {
		//			return rowLineEdits->isActiveWindow();
		//		});
		//	QObject::connect(
		//		*activeRowOfLineEdits,
		//		static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
		//		this,
		//		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changeTextSignal));
		//}
		this->m_pMediator->Notify(this, Commands::ChoosingOneObservationPoint);
	}
	else
	{
		//QObject::disconnect(
		//	*activeRowOfLineEdits,
		//	static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
		//	this,
		//	static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changeTextSignal));
		this->m_pMediator->Notify(this, Commands::ChoosingManyObservationPoints);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi(const std::size_t index)
{
	switch (index)
	{
	case 0:
		this->m_pMediator->Notify(this, Commands::EnteringPhi1);
		break;
	case 1:
		this->m_pMediator->Notify(this, Commands::EnteringPhi2);
		break;
	case 2:
		this->m_pMediator->Notify(this, Commands::EnteringPhi3);
		break;
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda(const std::size_t index)
{
	switch (index)
	{
	case 0:
		this->m_pMediator->Notify(this, Commands::EnteringLambda1);
		break;
	case 1:
		this->m_pMediator->Notify(this, Commands::EnteringLambda2);
		break;
	case 2:
		this->m_pMediator->Notify(this, Commands::EnteringLambda3);
		break;
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetH(const std::size_t index)
{
	switch (index)
	{
	case 0:
		this->m_pMediator->Notify(this, Commands::EnteringH1);
		break;
	case 1:
		this->m_pMediator->Notify(this, Commands::EnteringH2);
		break;
	case 2:
		this->m_pMediator->Notify(this, Commands::EnteringH3);
		break;
	}
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