#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class ObservationPoints : public Components
	{
		Q_OBJECT
	public:
		ObservationPoints(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ObservationPoints();
		void SetReadOnlyFirstColumn(bool a_bOn);
		void SetReadOnlyAllColumns(bool a_bOn);
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void IsConstObservationPoints(bool a_bChecked);
		void Items(int a_nIndex);
		void FirstColumn(bool a_bChecked);
		void SecondColumn(bool a_bChecked);
		void ThirdColumn(bool a_bChecked);
		void AddColumn();
		void IsOwnObservationPoints(bool a_bChecked);
	};
}
