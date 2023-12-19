#pragma once
#include "stdafx.h"
#include "Components.h"

namespace FirstInputParameters
{
	class FileResults : public Components
	{
		Q_OBJECT
	private:
		QString m_strOutputFilePath;
		//QFile m_toFile;
	public:
		FileResults(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~FileResults();
		void WhatWriteToFile(bool& isVectors, bool& isOrbitalParameters);
		bool WriteResultsToFile(
			const QString& methodName,
			const Vector3<double>& r_2,
			const Vector3<double>& v_2,
			const OrbitalParameters<double>& aOrbitalParameters);
		void ClearAll();
	private:
		void ReadSettings();
		void WriteSettings();
	public slots:
		void IsWriteToFile(bool a_bChecked);
		void AddPath();
		//void IsVectors(bool a_bChecked);
		//void IsOrbitalParameters(bool a_bChecked);
	};
}

