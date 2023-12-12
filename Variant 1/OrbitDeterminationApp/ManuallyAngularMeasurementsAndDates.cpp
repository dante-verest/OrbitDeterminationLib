#include "stdafx.h"
#include "ManuallyAngularMeasurementsAndDates.h"

SecondInputParameters::ManuallyAngularMeasurementsAndDate::ManuallyAngularMeasurementsAndDate(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, Mediator* aMediator) :
	Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->alphaLineEdit_1->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->deltaLineEdit_1->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->alphaLineEdit_2->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->deltaLineEdit_2->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->alphaLineEdit_3->setValidator(m_pDoubleValidator);
	m_pOrbitDeterminationAppClass->deltaLineEdit_3->setValidator(m_pDoubleValidator);

	this->ReadSettings();

	// first measurement
	QObject::connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha1);
	QObject::connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta1);
	QObject::connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_1,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate1);
	// second measurement
	QObject::connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha2);
	QObject::connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta2);
	QObject::connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_2,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate2);
	// third measurement
	QObject::connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha3);
	QObject::connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta3);
	QObject::connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_3,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate3);

	m_pOrbitDeterminationAppClass->spinBox->setSpecialValueText("1");
};

SecondInputParameters::ManuallyAngularMeasurementsAndDate::~ManuallyAngularMeasurementsAndDate()
{
	this->WriteSettings();
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually angular measurements and dates");

	m_pOrbitDeterminationAppClass->alphaLineEdit_1->setText(m_componentsSettings.value("/alpha 1", "").toString());
	m_pOrbitDeterminationAppClass->deltaLineEdit_1->setText(m_componentsSettings.value("/delta 1", "").toString());
	m_pOrbitDeterminationAppClass->dateTimeEdit_1->setDateTime(QDateTime(
		QDate(m_componentsSettings.value("/year 1", 2000).toInt(), 
			m_componentsSettings.value("/month 1", 01).toInt(), 
			m_componentsSettings.value("/day 1", 01).toInt()),
		QTime(m_componentsSettings.value("/hour 1", 00).toInt(),
			m_componentsSettings.value("/minute 1", 00).toInt(),
			m_componentsSettings.value("/second 1", 00).toInt(),
			m_componentsSettings.value("/millisecond 1", 000).toInt())));

	m_pOrbitDeterminationAppClass->alphaLineEdit_2->setText(m_componentsSettings.value("/alpha 2", "").toString());
	m_pOrbitDeterminationAppClass->deltaLineEdit_2->setText(m_componentsSettings.value("/delta 2", "").toString());
	m_pOrbitDeterminationAppClass->dateTimeEdit_2->setDateTime(QDateTime(
		QDate(m_componentsSettings.value("/year 2", 2000).toInt(),
			m_componentsSettings.value("/month 2", 01).toInt(),
			m_componentsSettings.value("/day 2", 01).toInt()),
		QTime(m_componentsSettings.value("/hour 2", 00).toInt(),
			m_componentsSettings.value("/minute 2", 00).toInt(),
			m_componentsSettings.value("/second 2", 00).toInt(),
			m_componentsSettings.value("/millisecond 2", 000).toInt())));

	m_pOrbitDeterminationAppClass->alphaLineEdit_3->setText(m_componentsSettings.value("/alpha 3", "").toString());
	m_pOrbitDeterminationAppClass->deltaLineEdit_3->setText(m_componentsSettings.value("/delta 3", "").toString());
	m_pOrbitDeterminationAppClass->dateTimeEdit_3->setDateTime(QDateTime(
		QDate(m_componentsSettings.value("/year 3", 2000).toInt(),
			m_componentsSettings.value("/month 3", 01).toInt(),
			m_componentsSettings.value("/day 3", 01).toInt()),
		QTime(m_componentsSettings.value("/hour 3", 00).toInt(),
			m_componentsSettings.value("/minute 3", 00).toInt(),
			m_componentsSettings.value("/second 3", 00).toInt(),
			m_componentsSettings.value("/millisecond 3", 000).toInt())));

	m_componentsSettings.endGroup();
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for manually angular measurements and dates");

	m_componentsSettings.setValue("/alpha 1", m_pOrbitDeterminationAppClass->alphaLineEdit_1->text());
	m_componentsSettings.setValue("/delta 1", m_pOrbitDeterminationAppClass->deltaLineEdit_1->text());

	m_componentsSettings.setValue("/year 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().date().year());
	m_componentsSettings.setValue("/month 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().date().month());
	m_componentsSettings.setValue("/day 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().date().day());
	m_componentsSettings.setValue("/hour 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().time().hour());
	m_componentsSettings.setValue("/minute 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().time().minute());
	m_componentsSettings.setValue("/second 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().time().second());
	m_componentsSettings.setValue("/millisecond 1", m_pOrbitDeterminationAppClass->dateTimeEdit_1->dateTime().time().msec());

	m_componentsSettings.setValue("/alpha 2", m_pOrbitDeterminationAppClass->alphaLineEdit_2->text());
	m_componentsSettings.setValue("/delta 2", m_pOrbitDeterminationAppClass->deltaLineEdit_2->text());

	m_componentsSettings.setValue("/year 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().date().year());
	m_componentsSettings.setValue("/month 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().date().month());
	m_componentsSettings.setValue("/day 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().date().day());
	m_componentsSettings.setValue("/hour 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().time().hour());
	m_componentsSettings.setValue("/minute 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().time().minute());
	m_componentsSettings.setValue("/second 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().time().second());
	m_componentsSettings.setValue("/millisecond 2", m_pOrbitDeterminationAppClass->dateTimeEdit_2->dateTime().time().msec());

	m_componentsSettings.setValue("/alpha 3", m_pOrbitDeterminationAppClass->alphaLineEdit_3->text());
	m_componentsSettings.setValue("/delta 3", m_pOrbitDeterminationAppClass->deltaLineEdit_3->text());

	m_componentsSettings.setValue("/year 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().date().year());
	m_componentsSettings.setValue("/month 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().date().month());
	m_componentsSettings.setValue("/day 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().date().day());
	m_componentsSettings.setValue("/hour 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().time().hour());
	m_componentsSettings.setValue("/minute 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().time().minute());
	m_componentsSettings.setValue("/second 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().time().second());
	m_componentsSettings.setValue("/millisecond 3", m_pOrbitDeterminationAppClass->dateTimeEdit_3->dateTime().time().msec());

	m_componentsSettings.endGroup();
};

double SecondInputParameters::ManuallyAngularMeasurementsAndDate::GetAngularMeasurement(
	const QLineEdit& lineEdit, bool* bOk)
{
	return lineEdit.text().toDouble(bOk);
};

Structures::Date&& SecondInputParameters::ManuallyAngularMeasurementsAndDate::GetDate(const QDateTimeEdit& dateTimeEdit)
{
	Structures::Date date;
	date.year = dateTimeEdit.dateTime().date().year();
	date.month = dateTimeEdit.dateTime().date().month();
	date.day = dateTimeEdit.dateTime().date().day();
	date.hour = dateTimeEdit.dateTime().time().hour();
	date.min = dateTimeEdit.dateTime().time().minute();
	date.sec = dateTimeEdit.dateTime().time().second() + dateTimeEdit.dateTime().time().msec() / 1000.0;
	return std::move(date);
};

bool SecondInputParameters::ManuallyAngularMeasurementsAndDate::GetAngularMeasurementsAndDates(
	std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
	std::array<Date, 3>& aDates)
{
	aAngularMeasurements[0].alpha = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->alphaLineEdit_1, &m_bOk[0]);
	aAngularMeasurements[0].delta = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->deltaLineEdit_1, &m_bOk[1]);
	aDates[0] = this->GetDate(
		*m_pOrbitDeterminationAppClass->dateTimeEdit_1);
	aAngularMeasurements[1].alpha = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->alphaLineEdit_2, &m_bOk[2]);
	aAngularMeasurements[1].delta = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->deltaLineEdit_2, &m_bOk[3]);
	aDates[1] = this->GetDate(
		*m_pOrbitDeterminationAppClass->dateTimeEdit_2);
	aAngularMeasurements[2].alpha = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->alphaLineEdit_3, &m_bOk[4]);
	aAngularMeasurements[2].delta = this->GetAngularMeasurement(
		*m_pOrbitDeterminationAppClass->deltaLineEdit_3, &m_bOk[5]);
	aDates[2] = this->GetDate(
		*m_pOrbitDeterminationAppClass->dateTimeEdit_3);
	if (std::all_of(m_bOk.begin(), m_bOk.end(), [](const bool& bOk) {
		return bOk == true;
		}))
		return true;
	else
		return false;
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetReadOnlyAllMeasurements(bool a_bOn)
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

//int SecondInputParameters::ManuallyAngularMeasurementsAndDate::valueFromText(const QString& text) const
//{
//	//static const QRegularExpression regExp(tr("(\\d+)(\\s*[xx]\\s*\\d+)?"));
//	//Q_ASSERT(regExp.isValid());
//
//	//const QRegularExpressionMatch match = regExp.match(text);
//	//if (match.isValid())
//	//	return match.captured(1).toInt();
//	//return 0;
//};
//
//QString SecondInputParameters::ManuallyAngularMeasurementsAndDate::textFromValue(int value) const
//{
//	//return tr("%1 x %1").arg(value);
//};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::ClearAll()
{
	m_pOrbitDeterminationAppClass->alphaLineEdit_1->clear();
	m_pOrbitDeterminationAppClass->deltaLineEdit_1->clear();
	m_pOrbitDeterminationAppClass->dateTimeEdit_1->clear();

	m_pOrbitDeterminationAppClass->alphaLineEdit_2->clear();
	m_pOrbitDeterminationAppClass->deltaLineEdit_2->clear();
	m_pOrbitDeterminationAppClass->dateTimeEdit_2->clear();

	m_pOrbitDeterminationAppClass->alphaLineEdit_3->clear();
	m_pOrbitDeterminationAppClass->deltaLineEdit_3->clear();
	m_pOrbitDeterminationAppClass->dateTimeEdit_3->clear();
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetAlpha1()
{
	this->m_pMediator->Notify(this, Commands::EnteringAlpha1);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDelta1()
{
	this->m_pMediator->Notify(this, Commands::EnteringDelta1);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDate1()
{
	this->m_pMediator->Notify(this, Commands::EnteringDate1);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetAlpha2()
{
	this->m_pMediator->Notify(this, Commands::EnteringAlpha2);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDelta2()
{
	this->m_pMediator->Notify(this, Commands::EnteringDelta2);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDate2()
{
	this->m_pMediator->Notify(this, Commands::EnteringDate2);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetAlpha3()
{
	this->m_pMediator->Notify(this, Commands::EnteringAlpha3);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDelta3()
{
	this->m_pMediator->Notify(this, Commands::EnteringDelta3);
};

void SecondInputParameters::ManuallyAngularMeasurementsAndDate::SetDate3()
{
	this->m_pMediator->Notify(this, Commands::EnteringDate3);
};