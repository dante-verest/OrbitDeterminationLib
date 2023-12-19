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
	const QString& aMethodName,
	const std::array<AngularMeasurements<double>, 3>& aAngularMeasurements,
	const std::array<Date, 3>& aDates,
	const std::array<ObservationPoint<double>, 3>& aObservationPoints,
	bool aDebugFile)
{
	bool bIsCalculatingSuccess = Method(aMethodName.toStdWString(), aAngularMeasurements, aDates, aObservationPoints,
		m_r_2, m_v_2, m_orbitalParameters, &m_calculationTime, aDebugFile);
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

const Vector3<double>& Buttons::GlobalButtons::Get_r_2()
{
	return this->m_r_2;
};

const Vector3<double>& Buttons::GlobalButtons::Get_v_2()
{
	return this->m_v_2;
};

const OrbitalParameters<double>& Buttons::GlobalButtons::GetOrbitalParameters()
{
	return this->m_orbitalParameters;
};

const std::chrono::microseconds& Buttons::GlobalButtons::GetCalculationTime()
{
	return this->m_calculationTime;
};