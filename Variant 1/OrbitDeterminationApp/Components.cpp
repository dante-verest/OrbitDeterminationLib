#include "stdafx.h"
#include "Components.h"

Components::Components(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass, 
	Mediator* aMediator) :
	m_pMediator(aMediator), m_pOrbitDeterminationAppClass(aOrbitDeterminationAppClass),
	m_pDoubleValidator(new QDoubleValidator)
{
	QLocale locale(QLocale::English);
	m_pDoubleValidator->setLocale(locale);
};

Components::~Components()
{}

void Components::SetMediator(Mediator* aMediator)
{
	this->m_pMediator = aMediator;
}
