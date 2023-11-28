#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class MeasurementMethod : public Components
	{
		Q_OBJECT
	public:
		MeasurementMethod(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~MeasurementMethod();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void Items(int a_nIndex);
	};
}

