#pragma once
#include "stdafx.h"
#include "Components.h"
#include "Date.h"

namespace SecondInputParameters
{
	class ManuallyAngularMeasurementsAndDate : public Components
	{
		Q_OBJECT
	private:
		std::array<AngularMeasurements<double>, 3> m_aAngularMeasurements;
		std::array<Date, 3> m_aDates;
		std::array<bool, 6> m_bOk;
	public:
		ManuallyAngularMeasurementsAndDate(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ManuallyAngularMeasurementsAndDate();

		void SetAngularMeasurements(const std::array<AngularMeasurements<double>, 3>& aAngularMeasurements);
		const std::array<AngularMeasurements<double>, 3>& GetAngularMeasurements();
		void SetDates(const std::array<Date, 3>& aDates);
		const std::array<Date, 3>& GetDates();

		//bool GetAngularMeasurementsAndDates(
		//	std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
		//	std::array<Date, 3>& aDates);
		void SetReadOnlyAllMeasurements(bool a_bOn);
		//int valueFromText(const QString& text) const override;
		//QString textFromValue(int value) const override;
		void ClearAll();
	private:
		double GetAngularMeasurement(QLineEdit* lineEdit, bool* bOk = nullptr);
		Structures::Date&& GetDate(QDateTimeEdit* dateTimeEdit);

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