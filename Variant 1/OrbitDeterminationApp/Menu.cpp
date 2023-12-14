#include "stdafx.h"
#include "Menu.h"

Menu::Menu::Menu(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	this->ReadSettings();

	connect(
		m_pOrbitDeterminationAppClass->debugAction,
		static_cast<void (QAction::*)(bool)>(&QAction::toggled),
		this,
		static_cast<void (Menu::*)(bool)>(&Menu::SetDebug));
};

Menu::Menu::~Menu()
{
	this->WriteSettings();
};

void Menu::Menu::ReadSettings()
{
	m_componentsSettings.beginGroup("/Settings for menu");

	m_pOrbitDeterminationAppClass->debugAction->setChecked(m_componentsSettings.value("/debug", false).toBool());
	
	m_componentsSettings.endGroup();
};

void Menu::Menu::WriteSettings()
{
	m_componentsSettings.beginGroup("/Settings for menu");

	m_componentsSettings.setValue("/debug", m_pOrbitDeterminationAppClass->debugAction->isChecked());

	m_componentsSettings.endGroup();
};

void Menu::Menu::SetDebug(bool a_isDebug)
{
	if (a_isDebug)
		this->m_pMediator->Notify(this, Commands::IsDebug);
	else
		this->m_pMediator->Notify(this, Commands::IsNotDebug);
};