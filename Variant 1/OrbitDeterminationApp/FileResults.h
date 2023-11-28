#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class FileResults : public Components
	{
		Q_OBJECT
	public:
		FileResults(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~FileResults();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		//void IsWriteToFile(bool a_bChecked);
		void AddPath();
		void IsVectors(bool a_bChecked);
		void IsOrbitalParameters(bool a_bChecked);
	};
}

