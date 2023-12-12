#pragma once
#include "stdafx.h"
#include "Components.h"
//#include "ObservationPoint.h"

namespace SecondInputParameters
{
	class ManuallyObservationPoints : public Components
	{
		Q_OBJECT
	private:
		std::array<std::array<QLineEdit*, 3>, 3> m_pObservationPointsLineEdits;
		std::array<bool, 9> m_bOk;
	public:
		ManuallyObservationPoints(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ManuallyObservationPoints();
		double GetObservationPointsField(const QLineEdit& lineEdit, bool* bOk = nullptr);
		bool GetObservationPoints(std::array<ObservationPoint<double>, 3>& aPoints);
		void ClearAll();
	private:
		void ReadSettings();
		void WriteSettings();
	signals:
		void changeTextSignal(const QString&);
	public slots:
		void IsOneObservationPoint(bool a_bChecked);
		void SetPhi(const std::size_t index);
		void SetLambda(const std::size_t index);
		void SetH(const std::size_t index);
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

