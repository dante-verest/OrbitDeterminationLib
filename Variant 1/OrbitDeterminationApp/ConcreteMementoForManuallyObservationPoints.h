#pragma once
#include "Memento.h"

namespace Memento
{
    class ConcreteMementoForManuallyObservationPoints : public Memento
    {
    private:
        bool m_bIsOneObservationPoint;
        QString m_strPhi1;
        QString m_strLambda1;
        QString m_strH1;
        QString m_strPhi2;
        QString m_strLambda2;
        QString m_strH2;
        QString m_strPhi3;
        QString m_strLambda3;
        QString m_strH3;
    public:
        ConcreteMementoForManuallyObservationPoints(
            bool isOneObservationPoint,
            const QString& phi1, const QString& lambda1, const QString& H1,
            const QString& phi2, const QString& lambda2, const QString& H2,
            const QString& phi3, const QString& lambda3, const QString& H3);
        ~ConcreteMementoForManuallyObservationPoints();

        bool operator ==(const ConcreteMementoForManuallyObservationPoints& other) const;

        bool IsOneObservationPoint();
        const QString& GetPhi1();
        const QString& GetLambda1();
        const QString& GetH1();
        const QString& GetPhi2();
        const QString& GetLambda2();
        const QString& GetH2();
        const QString& GetPhi3();
        const QString& GetLambda3();
        const QString& GetH3();
    };
}

