#pragma once
#include "stdafx.h"
#include "Components.h"

namespace Buttons
{
	class GlobalButtons : public Components
	{
		Q_OBJECT
	public:
		GlobalButtons(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
	public slots:
		void Calculate();
		void Clear();
	};
}
