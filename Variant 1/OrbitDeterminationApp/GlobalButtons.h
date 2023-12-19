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
		Vector3<double> m_r_2;
		Vector3<double> m_v_2;
		OrbitalParameters<double> m_orbitalParameters;
		std::chrono::microseconds m_calculationTime;
	public:
		GlobalButtons(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		bool Calculate(
			const QString& aMethodName,
			const std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
			const std::array<Date, 3>& aDates,
			const std::array<ObservationPoint<double>, 3>& aObservationPoints,
			bool aDebugFile = false);
		const Vector3<double>& Get_r_2();
		const Vector3<double>& Get_v_2();
		const OrbitalParameters<double>& GetOrbitalParameters();
		const std::chrono::microseconds& GetCalculationTime();
	public slots:
		void PushCalculate();
		void PushClear();
	};
}
