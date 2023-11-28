#include "stdafx.h"
#include "GlobalButtons.h"

Buttons::GlobalButtons::GlobalButtons(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	connect(
		m_pOrbitDeterminationAppClass->calculatePushButton,
		&QPushButton::pressed,
		this,
		&GlobalButtons::Calculate);
	connect(
		m_pOrbitDeterminationAppClass->clearPushButton,
		&QPushButton::pressed,
		this,
		&GlobalButtons::Clear);
};

void Buttons::GlobalButtons::Calculate()
{
	this->m_pMediator->Notify(this, Commands::Calculate);
};

void Buttons::GlobalButtons::Clear()
{
	this->m_pMediator->Notify(this, Commands::Clear);
};