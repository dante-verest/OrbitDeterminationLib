#pragma once
#include "stdafx.h"
#include "Components.h"
#include "Date.h"
#include "ConcreteMementoForManuallyAngularMeasurementsAndDates.h"

namespace SecondInputParameters
{
	class ManuallyAngularMeasurementsAndDate : public Components
	{
		Q_OBJECT
	private:
		std::array<Date, 3> m_aDates;
		std::array<AngularMeasurements<double>, 3> m_aAngularMeasurements;
		std::array<bool, 6> m_bOk;

		QCompleter* m_pCompleterToAlpha1;
		QCompleter* m_pCompleterToDelta1;
		QCompleter* m_pCompleterToAlpha2;
		QCompleter* m_pCompleterToDelta2;
		QCompleter* m_pCompleterToAlpha3;
		QCompleter* m_pCompleterToDelta3;
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

		Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates* Save();
		void Restore(Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates* memento);
		void SetVectorOfAngularMeasurementsAndDatesMementosToCompleters();

		void ClearAll();
	private:
		double GetAngularMeasurement(QLineEdit* lineEdit, bool* bOk = nullptr);
		Structures::Date&& GetDate(QDateTimeEdit* dateTimeEdit);

		void ReadSettings();
		void WriteSettings();
	public slots:
		void SetAlpha1();
		void HighlightedNewAlpha1(const QModelIndex& index);
		void ActivatedNewAlpha1(const QModelIndex& index);
		void SetDelta1();
		void HighlightedNewDelta1(const QModelIndex& index);
		void ActivatedNewDelta1(const QModelIndex& index);
		void SetDate1();
		void SetAlpha2();
		void HighlightedNewAlpha2(const QModelIndex& index);
		void ActivatedNewAlpha2(const QModelIndex& index);
		void SetDelta2();
		void HighlightedNewDelta2(const QModelIndex& index);
		void ActivatedNewDelta2(const QModelIndex& index);
		void SetDate2();
		void SetAlpha3();
		void HighlightedNewAlpha3(const QModelIndex& index);
		void ActivatedNewAlpha3(const QModelIndex& index);
		void SetDelta3();
		void HighlightedNewDelta3(const QModelIndex& index);
		void ActivatedNewDelta3(const QModelIndex& index);
		void SetDate3();
	};
}