#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class ObservationPoints : public Components
	{
		Q_OBJECT
	private:
		const QStringList m_observationPointsNames = { "Минск", "Большие Городятичи" };
		const std::vector<ObservationPoint<double>> m_observationPointsParameters = {
			{0.940863366518843216680138601023, 0.48109031203861475715914356205184, 0.23},
			{0.9166430446379730175123736722974, 0.49502094835161616439895615386899, 0.135} };
	public:
		ObservationPoints(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ObservationPoints();

		ObservationPoint<double>&& GetObservationPoint();
		bool IsConstObservationPoint();

		bool IsFirstColumn();
		bool IsSecondColumn();
		bool IsThirdColumn();

		bool IsManualObservationPoint();

		void SetCheckedAllCheckBoxes(bool a_bOn);
		void SetEnabledAllCheckBoxes(bool bOn);
		void SetEnabledComboBoxAndButton(bool bOn);

		//void ClearAll();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void IsConstObservationPoints(bool a_bChecked);
		//void Items(int a_nIndex);
		void FirstColumn(bool a_bChecked);
		void SecondColumn(bool a_bChecked);
		void ThirdColumn(bool a_bChecked);
		void AddColumn();
		void IsOwnObservationPoints(bool a_bChecked);
	};
}
