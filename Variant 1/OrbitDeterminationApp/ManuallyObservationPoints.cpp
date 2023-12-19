#include "stdafx.h"
#include "ManuallyObservationPoints.h"

SecondInputParameters::ManuallyObservationPoints::ManuallyObservationPoints(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	//m_pObservationPointsLineEdits = { {
	//	{m_pOrbitDeterminationAppClass->phiLineEdit_1,
	//		m_pOrbitDeterminationAppClass->phiLineEdit_2,
	//		m_pOrbitDeterminationAppClass->phiLineEdit_3},
	//	{m_pOrbitDeterminationAppClass->lambdaLineEdit_1,
	//		m_pOrbitDeterminationAppClass->lambdaLineEdit_2,
	//		m_pOrbitDeterminationAppClass->lambdaLineEdit_3},
	//	{m_pOrbitDeterminationAppClass->HlineEdit_1,
	//		m_pOrbitDeterminationAppClass->HlineEdit_2,
	//		m_pOrbitDeterminationAppClass->HlineEdit_3} } };

	connect(
		m_pOrbitDeterminationAppClass->oneObservationPointRadioButton,
		static_cast<void (QRadioButton::*)(bool)>(&QRadioButton::toggled),
		this,
		static_cast<void (ManuallyObservationPoints::*)(bool)>(&ManuallyObservationPoints::OneObservationPoint));

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

	// first column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetPhi1));
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_1,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetPhi1));

	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetLambda1));
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetLambda1));

	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_1,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetH1));
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_1,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetH1));

	// second column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetPhi2));
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_2,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetPhi2));

	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetLambda2));
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetLambda2));

	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_2,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetH2));
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_2,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetH2));

	// third column
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetPhi3));
	connect(
		m_pOrbitDeterminationAppClass->phiLineEdit_3,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetPhi3));

	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetLambda3));
	connect(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetLambda3));

	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_3,
		&QLineEdit::editingFinished,
		this,
		static_cast<void (ManuallyObservationPoints::*)(void)>(&ManuallyObservationPoints::SetH3));
	connect(
		m_pOrbitDeterminationAppClass->HlineEdit_3,
		&QLineEdit::textChanged,
		this,
		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetH3));

	//for (const auto& row : m_pObservationPointsLineEdits)
	//	for (const auto& col : row)
	//	{
	//		col->setValidator(m_pDoubleValidator);
	//		//connect(
	//		//	this,
	//		//	static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changedTextSignal),
	//		//	col,
	//		//	static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::setText));
	//		//connect(
	//		//	col,
	//		//	static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
	//		//	this,
	//		//	static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::SetText));
	//	}
};

SecondInputParameters::ManuallyObservationPoints::~ManuallyObservationPoints()
{
	this->WriteSettings();
};

void SecondInputParameters::ManuallyObservationPoints::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually observation points");

	m_bIsOneObservationPoint = m_componentsSettings.value("/one observation point", false).toBool();
	m_pOrbitDeterminationAppClass->oneObservationPointRadioButton->setChecked(m_bIsOneObservationPoint);

	m_aObservationPoints[0].phi = m_componentsSettings.value("/phi 1", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(QString::number(m_aObservationPoints[0].phi));
	m_pOrbitDeterminationAppClass->phiLineEdit_1->setReadOnly(m_componentsSettings.value("/phi 1 read only", true).toBool());
	m_aObservationPoints[0].lambda = m_componentsSettings.value("/lambda 1", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(QString::number(m_aObservationPoints[0].lambda));
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setReadOnly(m_componentsSettings.value("/lambda 1 read only", true).toBool());
	m_aObservationPoints[0].H = m_componentsSettings.value("/H 1", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->HlineEdit_1->setText(QString::number(m_aObservationPoints[0].H));
	m_pOrbitDeterminationAppClass->HlineEdit_1->setReadOnly(m_componentsSettings.value("/H 1 read only", true).toBool());
	m_pOrbitDeterminationAppClass->firstColumnGroupBox->setStyleSheet(m_componentsSettings.value("/first column style sheet", "").toString());

	m_aObservationPoints[1].phi = m_componentsSettings.value("/phi 2", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(QString::number(m_aObservationPoints[1].phi));
	m_pOrbitDeterminationAppClass->phiLineEdit_2->setReadOnly(m_componentsSettings.value("/phi 2 read only", true).toBool());
	m_aObservationPoints[1].lambda = m_componentsSettings.value("/lambda 2", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(QString::number(m_aObservationPoints[1].lambda));
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setReadOnly(m_componentsSettings.value("/lambda 2 read only", true).toBool());
	m_aObservationPoints[1].H = m_componentsSettings.value("/H 2", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->HlineEdit_2->setText(QString::number(m_aObservationPoints[1].H));
	m_pOrbitDeterminationAppClass->HlineEdit_2->setReadOnly(m_componentsSettings.value("/H 2 read only", true).toBool());
	m_pOrbitDeterminationAppClass->secondColumnGroupBox->setStyleSheet(m_componentsSettings.value("/second column style sheet", "").toString());

	m_aObservationPoints[2].phi = m_componentsSettings.value("/phi 3", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(QString::number(m_aObservationPoints[2].phi));
	m_pOrbitDeterminationAppClass->phiLineEdit_3->setReadOnly(m_componentsSettings.value("/phi 3 read only", true).toBool());
	m_aObservationPoints[2].lambda = m_componentsSettings.value("/lambda 3", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(QString::number(m_aObservationPoints[2].lambda));
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setReadOnly(m_componentsSettings.value("/lambda 3 read only", true).toBool());
	m_aObservationPoints[2].H = m_componentsSettings.value("/H 3", 0.0).toDouble();
	m_pOrbitDeterminationAppClass->HlineEdit_3->setText(QString::number(m_aObservationPoints[2].H));
	m_pOrbitDeterminationAppClass->HlineEdit_3->setReadOnly(m_componentsSettings.value("/H 3 read only", true).toBool());
	m_pOrbitDeterminationAppClass->thirdColumnGroupBox->setStyleSheet(m_componentsSettings.value("/third column style sheet", "").toString());

	m_componentsSettings.endGroup();
};

void SecondInputParameters::ManuallyObservationPoints::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually observation points");

	m_componentsSettings.setValue("/one observation point", m_bIsOneObservationPoint);

	m_componentsSettings.setValue("/phi 1", m_aObservationPoints[0].phi);
	m_componentsSettings.setValue("/phi 1 read only", m_pOrbitDeterminationAppClass->phiLineEdit_1->isReadOnly());
	m_componentsSettings.setValue("/lambda 1", m_aObservationPoints[0].lambda);
	m_componentsSettings.setValue("/lambda 1 read only", m_pOrbitDeterminationAppClass->lambdaLineEdit_1->isReadOnly());
	m_componentsSettings.setValue("/H 1", m_aObservationPoints[0].H);
	m_componentsSettings.setValue("/H 1 read only", m_pOrbitDeterminationAppClass->HlineEdit_1->isReadOnly());
	m_componentsSettings.setValue("/first column style sheet", m_pOrbitDeterminationAppClass->firstColumnGroupBox->styleSheet());

	m_componentsSettings.setValue("/phi 2", m_aObservationPoints[1].phi);
	m_componentsSettings.setValue("/phi 2 read only", m_pOrbitDeterminationAppClass->phiLineEdit_2->isReadOnly());
	m_componentsSettings.setValue("/lambda 2", m_aObservationPoints[1].lambda);
	m_componentsSettings.setValue("/lambda 2 read only", m_pOrbitDeterminationAppClass->lambdaLineEdit_2->isReadOnly());
	m_componentsSettings.setValue("/H 2", m_aObservationPoints[1].H);
	m_componentsSettings.setValue("/H 2 read only", m_pOrbitDeterminationAppClass->HlineEdit_2->isReadOnly());
	m_componentsSettings.setValue("/second column style sheet", m_pOrbitDeterminationAppClass->secondColumnGroupBox->styleSheet());

	m_componentsSettings.setValue("/phi 3", m_aObservationPoints[2].phi);
	m_componentsSettings.setValue("/phi 3 read only", m_pOrbitDeterminationAppClass->phiLineEdit_3->isReadOnly());
	m_componentsSettings.setValue("/lambda 3", m_aObservationPoints[2].lambda);
	m_componentsSettings.setValue("/lambda 3 read only", m_pOrbitDeterminationAppClass->lambdaLineEdit_3->isReadOnly());
	m_componentsSettings.setValue("/H 3", m_aObservationPoints[2].H);
	m_componentsSettings.setValue("/H 3 read only", m_pOrbitDeterminationAppClass->HlineEdit_3->isReadOnly());
	m_componentsSettings.setValue("/third column style sheet", m_pOrbitDeterminationAppClass->thirdColumnGroupBox->styleSheet());

	m_componentsSettings.endGroup();
};

bool SecondInputParameters::ManuallyObservationPoints::IsOneObservationPoint()
{
	return this->m_bIsOneObservationPoint;
};

void SecondInputParameters::ManuallyObservationPoints::SetHighlightedBorderToColumn(int aColumn, bool aOn)
{
	if (aOn)
		switch (aColumn)
		{
		case 0:
			m_pOrbitDeterminationAppClass->firstColumnGroupBox->setStyleSheet(m_strHighlightedBorderColumn);
			break;
		case 1:
			m_pOrbitDeterminationAppClass->secondColumnGroupBox->setStyleSheet(m_strHighlightedBorderColumn);
			break;
		case 2:
			m_pOrbitDeterminationAppClass->thirdColumnGroupBox->setStyleSheet(m_strHighlightedBorderColumn);
			break;
		}
	else
		switch (aColumn)
		{
		case 0:
			m_pOrbitDeterminationAppClass->firstColumnGroupBox->setStyleSheet(m_strDefaultBorderColumn);
			break;
		case 1:
			m_pOrbitDeterminationAppClass->secondColumnGroupBox->setStyleSheet(m_strDefaultBorderColumn);
			break;
		case 2:
			m_pOrbitDeterminationAppClass->thirdColumnGroupBox->setStyleSheet(m_strDefaultBorderColumn);
			break;
		}
};

void SecondInputParameters::ManuallyObservationPoints::SetObservationPointToColumn(
	int aColumn, const ObservationPoint<double>& aObservationPoint)
{
	switch (aColumn)
	{
	case 0:
		m_aObservationPoints[0] = aObservationPoint;
		m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(QString::number(m_aObservationPoints[0].phi));
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(QString::number(m_aObservationPoints[0].lambda));
		m_pOrbitDeterminationAppClass->HlineEdit_1->setText(QString::number(m_aObservationPoints[0].H));
		break;
	case 1:
		m_aObservationPoints[1] = aObservationPoint;
		m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(QString::number(m_aObservationPoints[1].phi));
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(QString::number(m_aObservationPoints[1].lambda));
		m_pOrbitDeterminationAppClass->HlineEdit_2->setText(QString::number(m_aObservationPoints[1].H));
		break;
	case 2:
		m_aObservationPoints[2] = aObservationPoint;
		m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(QString::number(m_aObservationPoints[2].phi));
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(QString::number(m_aObservationPoints[2].lambda));
		m_pOrbitDeterminationAppClass->HlineEdit_3->setText(QString::number(m_aObservationPoints[2].H));
		break;
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetObservationPoints(
	const std::array<ObservationPoint<double>, 3>& aPoints)
{
	this->m_aObservationPoints = aPoints;
};

const std::array<ObservationPoint<double>, 3>& SecondInputParameters::ManuallyObservationPoints::GetObservationPoints()
{
	return this->m_aObservationPoints;
};

void SecondInputParameters::ManuallyObservationPoints::SetReadOnlyAllColumns(bool a_bOn)
{
	m_pOrbitDeterminationAppClass->phiLineEdit_1->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->HlineEdit_1->setReadOnly(a_bOn);

	m_pOrbitDeterminationAppClass->phiLineEdit_2->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->HlineEdit_2->setReadOnly(a_bOn);

	m_pOrbitDeterminationAppClass->phiLineEdit_3->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setReadOnly(a_bOn);
	m_pOrbitDeterminationAppClass->HlineEdit_3->setReadOnly(a_bOn);
};


double SecondInputParameters::ManuallyObservationPoints::GetObservationPointsFromLineEdit(
	QLineEdit* lineEdit, bool* bOk)
{
	return lineEdit->text().toDouble(bOk);
};

bool SecondInputParameters::ManuallyObservationPoints::GetObservationPointsFromLineEdits()
{
	m_aObservationPoints[0].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_1, &m_bOk[0]);
	m_aObservationPoints[0].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1, &m_bOk[1]);
	m_aObservationPoints[0].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_1, &m_bOk[2]);
	m_aObservationPoints[1].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_2, &m_bOk[3]);
	m_aObservationPoints[1].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2, &m_bOk[4]);
	m_aObservationPoints[1].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_2, &m_bOk[5]);
	m_aObservationPoints[2].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_3, &m_bOk[6]);
	m_aObservationPoints[2].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3, &m_bOk[7]);
	m_aObservationPoints[2].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_3, &m_bOk[8]);
	return std::all_of(m_bOk.begin(), m_bOk.end(), [](const bool& bOk) {
		return bOk == true; });
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

void SecondInputParameters::ManuallyObservationPoints::OneObservationPoint(bool a_bChecked)
{
	this->m_bIsOneObservationPoint = a_bChecked;
	if (a_bChecked)
	{

		//for (auto elem = activeRowOfLineEdits->begin(); elem != activeRowOfLineEdits->end(); ++elem)
		//	connect(
		//		*elem,
		//		static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
		//		this,
		//		static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changedTextSignal));
	}
	else
	{
		//disconnect(
		//	*activeRowOfLineEdits,
		//	static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
		//	this,
		//	static_cast<void (ManuallyObservationPoints::*)(const QString&)>(&ManuallyObservationPoints::changedTextSignal));
		//this->m_pMediator->Notify(this, Commands::ChoosingManyObservationPoints);
	}
	this->m_pMediator->Notify(this, Commands::ChoosingOneObservationPoint);
};

//void SecondInputParameters::ManuallyObservationPoints::SetPhi(const std::size_t index)
//{
//	switch (index)
//	{
//	case 0:
//		this->m_pMediator->Notify(this, Commands::EnteringPhi1);
//		break;
//	case 1:
//		this->m_pMediator->Notify(this, Commands::EnteringPhi2);
//		break;
//	case 2:
//		this->m_pMediator->Notify(this, Commands::EnteringPhi3);
//		break;
//	}
//};
//
//void SecondInputParameters::ManuallyObservationPoints::SetLambda(const std::size_t index)
//{
//	switch (index)
//	{
//	case 0:
//		this->m_pMediator->Notify(this, Commands::EnteringLambda1);
//		break;
//	case 1:
//		this->m_pMediator->Notify(this, Commands::EnteringLambda2);
//		break;
//	case 2:
//		this->m_pMediator->Notify(this, Commands::EnteringLambda3);
//		break;
//	}
//};
//
//void SecondInputParameters::ManuallyObservationPoints::SetH(const std::size_t index)
//{
//	switch (index)
//	{
//	case 0:
//		this->m_pMediator->Notify(this, Commands::EnteringH1);
//		break;
//	case 1:
//		this->m_pMediator->Notify(this, Commands::EnteringH2);
//		break;
//	case 2:
//		this->m_pMediator->Notify(this, Commands::EnteringH3);
//		break;
//	}
//};

//void SecondInputParameters::ManuallyObservationPoints::SetText(const QString& str)
//{
//	std::array<QLineEdit*, 3>::iterator activeRowOfLineEdits;
//	if (m_bIsOneObservationPoint)
//	{
//		for (auto row = m_pObservationPointsLineEdits.begin(); row != m_pObservationPointsLineEdits.end(); ++row)
//		{
//			activeRowOfLineEdits = std::partition_point(row->begin(), row->end(),
//				[](const QLineEdit* rowLineEdits) {
//					return !rowLineEdits->isActiveWindow();
//				});
//			if (activeRowOfLineEdits != row->end())
//			{
//				for (auto elem = row->begin(); elem != (row->end() - 1); ++elem)
//				{
//					elem[0]->setText(str);
//					elem[2]->setText(str);
//				}
//				break;
//			}
//		}
//	}
//};

void SecondInputParameters::ManuallyObservationPoints::SetPhi1()
{
	//this->m_pMediator->Notify(this, Commands::EnteringPhi1);
	m_aObservationPoints[0].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_1, &m_bOk[0]);
	//if (m_bIsOneObservationPoint)
	//	emit changedTextSignal(QString::number(m_aObservationPoints[0].phi));
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi1(const QString& phi1)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(phi1);
		m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(phi1);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda1()
{
	//this->m_pMediator->Notify(this, Commands::EnteringLambda1);
	m_aObservationPoints[0].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1, &m_bOk[1]);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda1(const QString& lambda1)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(lambda1);
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(lambda1);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetH1()
{
	//this->m_pMediator->Notify(this, Commands::EnteringH1);
	m_aObservationPoints[0].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_1, &m_bOk[2]);
};

void SecondInputParameters::ManuallyObservationPoints::SetH1(const QString& H1)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->HlineEdit_2->setText(H1);
		m_pOrbitDeterminationAppClass->HlineEdit_3->setText(H1);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi2()
{
	//this->m_pMediator->Notify(this, Commands::EnteringPhi2);
	m_aObservationPoints[1].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_2, &m_bOk[3]);
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi2(const QString& phi2)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(phi2);
		m_pOrbitDeterminationAppClass->phiLineEdit_3->setText(phi2);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda2()
{
	//this->m_pMediator->Notify(this, Commands::EnteringLambda2);
	m_aObservationPoints[1].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2, &m_bOk[4]);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda2(const QString& lambda2)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(lambda2);
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3->setText(lambda2);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetH2()
{
	//this->m_pMediator->Notify(this, Commands::EnteringH2);
	m_aObservationPoints[1].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_2, &m_bOk[5]);
};

void SecondInputParameters::ManuallyObservationPoints::SetH2(const QString& H2)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->HlineEdit_1->setText(H2);
		m_pOrbitDeterminationAppClass->HlineEdit_3->setText(H2);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi3()
{
	//this->m_pMediator->Notify(this, Commands::EnteringPhi3);
	m_aObservationPoints[2].phi = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->phiLineEdit_3, &m_bOk[6]);
};

void SecondInputParameters::ManuallyObservationPoints::SetPhi3(const QString& phi3)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->phiLineEdit_1->setText(phi3);
		m_pOrbitDeterminationAppClass->phiLineEdit_2->setText(phi3);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda3()
{
	//this->m_pMediator->Notify(this, Commands::EnteringLambda3);
	m_aObservationPoints[2].lambda = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->lambdaLineEdit_3, &m_bOk[7]);
};

void SecondInputParameters::ManuallyObservationPoints::SetLambda3(const QString& lambda3)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->lambdaLineEdit_1->setText(lambda3);
		m_pOrbitDeterminationAppClass->lambdaLineEdit_2->setText(lambda3);
	}
};

void SecondInputParameters::ManuallyObservationPoints::SetH3()
{
	//this->m_pMediator->Notify(this, Commands::EnteringH3);
	m_aObservationPoints[2].H = this->GetObservationPointsFromLineEdit(
		m_pOrbitDeterminationAppClass->HlineEdit_3, &m_bOk[8]);
};

void SecondInputParameters::ManuallyObservationPoints::SetH3(const QString& H3)
{
	if (m_bIsOneObservationPoint)
	{
		m_pOrbitDeterminationAppClass->HlineEdit_1->setText(H3);
		m_pOrbitDeterminationAppClass->HlineEdit_2->setText(H3);
	}
};