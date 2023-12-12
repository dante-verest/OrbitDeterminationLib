#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class AngularMeasurementsAndDate : public Components
	{
		Q_OBJECT
	private:
		QString m_strTLEfilePath;
	public:
		AngularMeasurementsAndDate(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~AngularMeasurementsAndDate();
		void ClearAll();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void Manually(bool a_bChecked);
		void FromFile(bool a_bChecked);
		void FromTLEfile(bool a_bChecked);
		void AddFilePath();
	};
}
