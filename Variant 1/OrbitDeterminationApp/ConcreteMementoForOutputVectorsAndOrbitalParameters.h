#pragma once
#include "Memento.h"

namespace Memento
{
    class ConcreteMementoForOutputVectorsAndOrbitalParameters : public Memento
    {
    private:
        QString m_strMethodName;
        QString m_str_r2;
        QString m_str_v2;
        QString m_strInclination;
        QString m_strRightAscentionOfTheAscendingNode;
        QString m_strArgumentOfPerigee;
        QString m_strEccentricity;
        QString m_strLargeSemiaxis;
        QString m_strTrueAnomaly;
        QString m_strAngularMomentum;
    public:
        ConcreteMementoForOutputVectorsAndOrbitalParameters(
            const QString& methodName, const QString& r_2, const QString& v_2,
            const QString& inclination, const QString& rightAscentionOfTheAscendingNode, 
            const QString& argumentOfPerigee, const QString& eccentricity, 
            const QString& largeSemiaxis, const QString& trueAnomaly, 
            const QString& angularMomentum);
        ~ConcreteMementoForOutputVectorsAndOrbitalParameters();

        bool operator ==(const ConcreteMementoForOutputVectorsAndOrbitalParameters& other) const;

        const QString& GetMethodName();
        const QString& Get_r_2();
        const QString& Get_v_2();
        const QString& GetInclination();
        const QString& GetRightAscentionOfTheAscendingNode();
        const QString& GetArgumentOfPerigee();
        const QString& GetEccentricity();
        const QString& GetLargeSemiaxis();
        const QString& GetTrueAnomaly();
        const QString& GetAngularMomentum();
    };
}

