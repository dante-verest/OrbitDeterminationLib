#pragma once
#include "stdafx.h"
#include "Components.h"
//#include "ObservationPoint.h"

namespace SecondInputParameters
{
	class ManuallyObservationPoints : public Components
	{
		Q_OBJECT
	public:
		ManuallyObservationPoints(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ManuallyObservationPoints();
		double GetObservationPointsField(const QLineEdit& lineEdit);
		//Structures::ObservationPoint<double> GetObservationPoint()
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void IsOneObservationPoint(bool a_bChecked);
		void SetPhi1();
		void SetLambda1();
		void SetH1();
		void SetPhi2();
		void SetLambda2();
		void SetH2();
		void SetPhi3();
		void SetLambda3();
		void SetH3();
	};
}

