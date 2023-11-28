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
	connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha1);
	connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_1,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta1);
	connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_1,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate1);
	// second measurement
	connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha2);
	connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_2,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta2);
	connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_2,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate2);
	// third measurement
	connect(
		m_pOrbitDeterminationAppClass->alphaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetAlpha3);
	connect(
		m_pOrbitDeterminationAppClass->deltaLineEdit_3,
		&QLineEdit::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDelta3);
	connect(
		m_pOrbitDeterminationAppClass->dateTimeEdit_3,
		&QAbstractSpinBox::editingFinished,
		this,
		&ManuallyAngularMeasurementsAndDate::SetDate3);
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

double SecondInputParameters::ManuallyAngularMeasurementsAndDate::GetAngularMeasurement(const QLineEdit& lineEdit)
{
	return lineEdit.text().toDouble();
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