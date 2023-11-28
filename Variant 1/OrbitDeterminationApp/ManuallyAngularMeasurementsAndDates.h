#pragma once
#include "stdafx.h"
#include "Components.h"
#include "Date.h"

namespace SecondInputParameters
{
	class ManuallyAngularMeasurementsAndDate : public Components
	{
		Q_OBJECT
	public:
		ManuallyAngularMeasurementsAndDate(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ManuallyAngularMeasurementsAndDate();
		double GetAngularMeasurement(const QLineEdit& lineEdit);
		Structures::Date&& GetDate(const QDateTimeEdit& dateTimeEdit);
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void SetAlpha1();
		void SetDelta1();
		void SetDate1();
		void SetAlpha2();
		void SetDelta2();
		void SetDate2();
		void SetAlpha3();
		void SetDelta3();
		void SetDate3();
	};
}