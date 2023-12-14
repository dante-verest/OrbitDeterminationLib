#pragma once
#include "stdafx.h"
#include "Components.h"

namespace Menu
{
    class Menu : public Components
    {
        Q_OBJECT
    public:
        Menu(
            Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
            Mediator* aMediator);
        ~Menu();
    private:
        void ReadSettings();
        void WriteSettings();
    public slots:
        void SetDebug(bool a_isDebug);
    };
}

