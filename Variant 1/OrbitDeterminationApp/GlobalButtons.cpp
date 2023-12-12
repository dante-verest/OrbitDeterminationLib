#include "stdafx.h"
#include "GlobalButtons.h"

Buttons::GlobalButtons::GlobalButtons(
	Ui::OrbitDeterminationAppClass* aOrbitDeterminationAppClass,
	Mediator* aMediator) : Components(aOrbitDeterminationAppClass, aMediator)
{
	connect(
		m_pOrbitDeterminationAppClass->calculatePushButton,
		&QPushButton::pressed,
		this,
		&GlobalButtons::PushCalculate);
	connect(
		m_pOrbitDeterminationAppClass->clearPushButton,
		&QPushButton::pressed,
		this,
		&GlobalButtons::PushClear);
};

void Buttons::GlobalButtons::PushCalculate()
{
	this->m_pMediator->Notify(this, Commands::Calculate);
};

void Buttons::GlobalButtons::PushClear()
{
	this->m_pMediator->Notify(this, Commands::Clear);
};

bool Buttons::GlobalButtons::Calculate(
	const char* aMethodName,
	const std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
	const std::array<Date, 3>& aDates,
	const std::array<ObservationPoint<double>, 3>& aObservationPoints,
	Vector3<double>& r_2,
	Vector3<double>& v_2,
	OrbitalParameters<double>& aOrbitalParameters,
	std::chrono::microseconds* aCalculateTime,
	bool aDebugFile)
{
	bool bIsCalculatingSuccess = Method(aMethodName, aAngularMeasurements, aDates, aObservationPoints,
		r_2, v_2, aOrbitalParameters, aCalculateTime, aDebugFile);
	if (bIsCalculatingSuccess)
	{
		return bIsCalculatingSuccess;
	}
	else
	{
		m_messageBox.setText("The " + QString(aMethodName) + " method failed! There are maybe UNDERFLOW, \n"
			"OVERFLOW or ZERODIVIDE exceptions!\nAlso maybe there are limit of iterations (100000)!\n"
			"Try to enter other input numbers!");
		m_messageBox.setIcon(QMessageBox::Critical);
		m_messageBox.exec();
		return bIsCalculatingSuccess;
	}
};