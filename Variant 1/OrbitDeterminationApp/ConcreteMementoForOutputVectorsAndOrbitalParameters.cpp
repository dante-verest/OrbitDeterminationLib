#include "stdafx.h"
#include "ConcreteMementoForOutputVectorsAndOrbitalParameters.h"

Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::
ConcreteMementoForOutputVectorsAndOrbitalParameters(
    const QString& methodName, const QString& r_2, const QString& v_2,
    const QString& inclination, const QString& rightAscentionOfTheAscendingNode,
    const QString& argumentOfPerigee, const QString& eccentricity,
    const QString& largeSemiaxis, const QString& trueAnomaly,
    const QString& angularMomentum) :
    m_strMethodName(methodName), m_str_r2(r_2), m_str_v2(v_2),
    m_strInclination(inclination), m_strRightAscentionOfTheAscendingNode(rightAscentionOfTheAscendingNode),
    m_strArgumentOfPerigee(argumentOfPerigee), m_strEccentricity(eccentricity),
    m_strLargeSemiaxis(largeSemiaxis), m_strTrueAnomaly(trueAnomaly),
    m_strAngularMomentum(angularMomentum)
{
    this->ReadSettings();
};

Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::
~ConcreteMementoForOutputVectorsAndOrbitalParameters()
{
    this->WriteSettings();
};

bool Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::operator==(
    const ConcreteMementoForOutputVectorsAndOrbitalParameters& other) const
{
    return (
        this->m_strMethodName == other.m_strMethodName &&
        this->m_str_r2 == other.m_str_r2 &&
        this->m_str_v2 == other.m_str_v2 &&
        this->m_strInclination == other.m_strInclination &&
        this->m_strRightAscentionOfTheAscendingNode == other.m_strRightAscentionOfTheAscendingNode &&
        this->m_strArgumentOfPerigee == other.m_strArgumentOfPerigee &&
        this->m_strEccentricity == other.m_strEccentricity &&
        this->m_strLargeSemiaxis == other.m_strLargeSemiaxis &&
        this->m_strTrueAnomaly == other.m_strTrueAnomaly &&
        this->m_strAngularMomentum == other.m_strAngularMomentum);
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetMethodName()
{
    return this->m_strMethodName;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::Get_r_2()
{
    return this->m_str_r2;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::Get_v_2()
{
    return this->m_str_v2;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetInclination()
{
    return this->m_strInclination;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetRightAscentionOfTheAscendingNode()
{
    return this->m_strRightAscentionOfTheAscendingNode;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetArgumentOfPerigee()
{
    return this->m_strArgumentOfPerigee;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetEccentricity()
{
    return this->m_strEccentricity;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetLargeSemiaxis()
{
    return this->m_strLargeSemiaxis;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetTrueAnomaly()
{
    return this->m_strTrueAnomaly;
};

const QString& Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters::GetAngularMomentum()
{
    return this->m_strAngularMomentum;
};