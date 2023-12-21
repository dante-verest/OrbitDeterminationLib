#include "stdafx.h"
#include "ConcreteMementoForManuallyAngularMeasurementsAndDates.h"

Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::
ConcreteMementoForManuallyAngularMeasurementsAndDates(
	const QString& alpha1, const QString& delta1, const Structures::Date& dateTime1,
	const QString& alpha2, const QString& delta2, const Structures::Date& dateTime2,
	const QString& alpha3, const QString& delta3, const Structures::Date& dateTime3) :
	m_strAlpha1(alpha1), m_strDelta1(delta1), m_strDateTime1(dateTime1),
	m_strAlpha2(alpha2), m_strDelta2(delta2), m_strDateTime2(dateTime2),
	m_strAlpha3(alpha3), m_strDelta3(delta3), m_strDateTime3(dateTime3)
{};

Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::
~ConcreteMementoForManuallyAngularMeasurementsAndDates()
{};

bool Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::operator==(
	const ConcreteMementoForManuallyAngularMeasurementsAndDates& other) const
{
	return (
		this->m_strAlpha1 == other.m_strAlpha1 &&
		this->m_strDelta1 == other.m_strDelta1 &&
		this->m_strDateTime1 == other.m_strDateTime1 &&
		this->m_strAlpha2 == other.m_strAlpha2 &&
		this->m_strDelta2 == other.m_strDelta2 &&
		this->m_strDateTime2 == other.m_strDateTime2 &&
		this->m_strAlpha3 == other.m_strAlpha3 &&
		this->m_strDelta3 == other.m_strDelta3 &&
		this->m_strDateTime3 == other.m_strDateTime3);
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetAlpha1()
{
	return this->m_strAlpha1;
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDelta1()
{
	return this->m_strDelta1;
};

const Structures::Date& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDateTime1()
{
	return this->m_strDateTime1;
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetAlpha2()
{
	return this->m_strAlpha2;
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDelta2()
{
	return this->m_strDelta2;
};

const Structures::Date& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDateTime2()
{
	return this->m_strDateTime2;
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetAlpha3()
{
	return this->m_strAlpha3;
};

const QString& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDelta3()
{
	return this->m_strDelta3;
};

const Structures::Date& Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates::GetDateTime3()
{
	return this->m_strDateTime3;
};