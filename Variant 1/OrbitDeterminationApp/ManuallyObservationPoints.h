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
		bool m_bIsOneObservationPoint;
		std::array<ObservationPoint<double>, 3> m_aObservationPoints;
		//std::array<std::array<QLineEdit*, 3>, 3> m_pObservationPointsLineEdits;
		std::array<bool, 9> m_bOk;
		const QString m_strHighlightedBorderColumn = "QGroupBox { background-color: rgba(224, 0, 0, 127); }";
		const QString m_strDefaultBorderColumn = "QGroupBox { background-color: rgba(255, 255, 255, 127); }";
	public:
		ManuallyObservationPoints(
			Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
			Mediator* aMediator);
		~ManuallyObservationPoints();

		bool IsOneObservationPoint();
		void SetHighlightedBorderToColumn(int aColumn, bool aOn);
		void SetObservationPointToColumn(int aColumn, const ObservationPoint<double>& aObservationPoint);
		void SetObservationPoints(const std::array<ObservationPoint<double>, 3>& aPoints);
		const std::array<ObservationPoint<double>, 3>& GetObservationPoints();
		void SetReadOnlyAllColumns(bool a_bOn);

		bool GetObservationPointsFromLineEdits();

		void ClearAll();
	private:
		double GetObservationPointsFromLineEdit(QLineEdit* lineEdit, bool* bOk = nullptr);

		void ReadSettings();
		void WriteSettings();
	signals:
		void changedTextSignal(const QString&);
	public slots:
		void OneObservationPoint(bool a_bChecked);
		//void SetPhi(const std::size_t index);
		//void SetLambda(const std::size_t index);
		//void SetH(const std::size_t index);
		//void SetText(const QString&);
		void SetPhi1();
		void SetPhi1(const QString& phi1);
		void SetLambda1();
		void SetLambda1(const QString& lambda1);
		void SetH1();
		void SetH1(const QString& H1);
		void SetPhi2();
		void SetPhi2(const QString& phi2);
		void SetLambda2();
		void SetLambda2(const QString& lambda2);
		void SetH2();
		void SetH2(const QString& H2);
		void SetPhi3();
		void SetPhi3(const QString& phi3);
		void SetLambda3();
		void SetLambda3(const QString& lambda3);
		void SetH3();
		void SetH3(const QString& H3);
	};
}

