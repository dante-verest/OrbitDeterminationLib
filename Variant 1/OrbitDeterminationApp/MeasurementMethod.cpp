#include "stdafx.h"
#include "MeasurementMethod.h"

FirstInputParameters::MeasurementMethod::MeasurementMethod(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	m_pOrbitDeterminationAppClass->methodComboBox->addItem("Метод Гаусса");
	m_pOrbitDeterminationAppClass->methodComboBox->addItem("Метод Лапласа");
	m_pOrbitDeterminationAppClass->methodComboBox->addItem("Метод Эскобала");

	this->ReadSettings();

	//this->Items(m_pOrbitDeterminationAppClass->methodComboBox->currentIndex());

	connect(
		m_pOrbitDeterminationAppClass->methodComboBox,
		static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		this,
		static_cast<void (MeasurementMethod::*)(int)>(&MeasurementMethod::Items));
};

FirstInputParameters::MeasurementMethod::~MeasurementMethod()
{
	this->WriteSettings();
};

void FirstInputParameters::MeasurementMethod::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for measurement methods");

	m_pOrbitDeterminationAppClass->methodComboBox->setCurrentIndex(m_componentsSettings.value("/current method", 0).toInt());
	//this->Items(m_pOrbitDeterminationAppClass->methodComboBox->currentIndex());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::MeasurementMethod::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for measurement methods");

	m_componentsSettings.setValue("/current method", m_pOrbitDeterminationAppClass->methodComboBox->currentIndex());

	m_componentsSettings.endGroup();
};

void FirstInputParameters::MeasurementMethod::Items(int a_nIndex)
{
	switch (a_nIndex)
	{
	case 0:
		this->m_pMediator->Notify(this, Commands::ChoosingGaussMethod);
		break;
	case 1:
		this->m_pMediator->Notify(this, Commands::ChoosingLaplasMethod);
		break;
	case 2:
		this->m_pMediator->Notify(this, Commands::ChoosingEscobalMethod);
		break;
	}
};

QString FirstInputParameters::MeasurementMethod::GetCurrentItem()
{
	int index = m_pOrbitDeterminationAppClass->methodComboBox->currentIndex();
	QString methodName;
	switch (index)
	{
	case 0:
		methodName = "Gauss";
		break;
	case 1:
		methodName = "Laplas";
		break;
	case 2:
		methodName = "Escobal";
		break;
	}
	return methodName;
};