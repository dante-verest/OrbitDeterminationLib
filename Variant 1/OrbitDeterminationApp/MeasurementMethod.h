#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class MeasurementMethod : public Components
	{
		Q_OBJECT
	private:
		const QStringList m_methodNames = {
			"Метод Гаусса", "Метод Лапласа", "Метод Эскобала" };
		//int m_nCurrentIndex;
	public:
		MeasurementMethod(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~MeasurementMethod();
		QString&& GetCurrentItem();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		//void Items(int a_nIndex);
	};
}

