#include "stdafx.h"
#include "StatusBar.h"

StatusBar::StatusBar::StatusBar(
    Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
    Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
    this->ReadSettings();
};

StatusBar::StatusBar::~StatusBar()
{
    this->WriteSettings();
};

void StatusBar::StatusBar::ReadSettings()
{
    m_componentsSettings.beginGroup("/Settings for status bar");

    m_pOrbitDeterminationAppClass->statusBar->showMessage(m_componentsSettings.value("/status bar message", "").toString());

    m_componentsSettings.endGroup();
};

void StatusBar::StatusBar::WriteSettings()
{
    m_componentsSettings.beginGroup("/Settings for status bar");

    m_componentsSettings.setValue("/status bar message", m_pOrbitDeterminationAppClass->statusBar->currentMessage());

    m_componentsSettings.endGroup();
};

void StatusBar::StatusBar::AddMessage(const QString& message)
{
    m_pOrbitDeterminationAppClass->statusBar->showMessage(message);
};

void StatusBar::StatusBar::Clear()
{
    m_pOrbitDeterminationAppClass->statusBar->clearMessage();
};