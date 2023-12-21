#include "stdafx.h"
#include "ConcreteMementoForManuallyObservationPoints.h"

Memento::ConcreteMementoForManuallyObservationPoints::
ConcreteMementoForManuallyObservationPoints(
    bool isOneObservationPoint,
    const QString& phi1, const QString& lambda1, const QString& H1,
    const QString& phi2, const QString& lambda2, const QString& H2,
    const QString& phi3, const QString& lambda3, const QString& H3) :
    m_bIsOneObservationPoint(isOneObservationPoint),
    m_strPhi1(phi1), m_strLambda1(lambda1), m_strH1(H1),
    m_strPhi2(phi2), m_strLambda2(lambda2), m_strH2(H2),
    m_strPhi3(phi3), m_strLambda3(lambda3), m_strH3(H3)
{};

Memento::ConcreteMementoForManuallyObservationPoints::
~ConcreteMementoForManuallyObservationPoints()
{};

bool Memento::ConcreteMementoForManuallyObservationPoints::operator==(
    const ConcreteMementoForManuallyObservationPoints& other) const
{
    return (
        this->m_strPhi1 == other.m_strPhi1 &&
        this->m_strLambda1 == other.m_strLambda1 &&
        this->m_strH1 == other.m_strH1 &&
        this->m_strPhi2 == other.m_strPhi2 &&
        this->m_strLambda2 == other.m_strLambda2 &&
        this->m_strH2 == other.m_strH2 &&
        this->m_strPhi3 == other.m_strPhi3 &&
        this->m_strLambda3 == other.m_strLambda3 &&
        this->m_strH3 == other.m_strH3);
};

bool Memento::ConcreteMementoForManuallyObservationPoints::IsOneObservationPoint()
{
    return this->m_bIsOneObservationPoint;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetPhi1()
{
    return this->m_strPhi1;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetLambda1()
{
    return this->m_strLambda1;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetH1()
{
    return this->m_strH1;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetPhi2()
{
    return this->m_strPhi2;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetLambda2()
{
    return this->m_strLambda2;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetH2()
{
    return this->m_strH2;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetPhi3()
{
    return this->m_strPhi3;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetLambda3()
{
    return this->m_strLambda3;
};

const QString& Memento::ConcreteMementoForManuallyObservationPoints::GetH3()
{
    return this->m_strH3;
};