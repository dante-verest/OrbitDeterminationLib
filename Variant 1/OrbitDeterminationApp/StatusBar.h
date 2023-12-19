#pragma once
#include "Components.h"
#include "stdarg.h"

namespace StatusBar
{
    class StatusBar : public Components
    {
        Q_OBJECT
    public:
        StatusBar(Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
            Mediator* aMediator);
        ~StatusBar();

        void AddMessage(const QString& message);

        void Clear();
    private:
        void ReadSettings();
        void WriteSettings();
    };
}

