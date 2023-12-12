#pragma once
#include "stdafx.h"
#include "Components.h"

namespace Buttons
{
	class GlobalButtons : public Components
	{
		Q_OBJECT
	private:
		QMessageBox m_messageBox;
	public:
		GlobalButtons(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		bool Calculate(
			const char* aMethodName,
			const std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
			const std::array<Date, 3>& aDates,
			const std::array<ObservationPoint<double>, 3>& aObservationPoints,
			Vector3<double>& r_2,
			Vector3<double>& v_2,
			OrbitalParameters<double>& aOrbitalParameters,
			std::chrono::microseconds* aCalculateTime = nullptr,
			bool aDebugFile = false);
	public slots:
		void PushCalculate();
		void PushClear();
	};
}
