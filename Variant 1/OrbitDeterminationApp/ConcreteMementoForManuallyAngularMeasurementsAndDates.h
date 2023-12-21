#pragma once
#include "Memento.h"
#include "Date.h"

namespace Memento
{
    class ConcreteMementoForManuallyAngularMeasurementsAndDates : public Memento
    {
    private:
        QString m_strAlpha1;
        QString m_strDelta1;
        Structures::Date m_strDateTime1;
        QString m_strAlpha2;
        QString m_strDelta2;
        Structures::Date m_strDateTime2;
        QString m_strAlpha3;
        QString m_strDelta3;
        Structures::Date m_strDateTime3;
    public:
        ConcreteMementoForManuallyAngularMeasurementsAndDates(
            const QString& alpha1, const QString& delta1, const Structures::Date& dateTime1,
            const QString& alpha2, const QString& delta2, const Structures::Date& dateTime2,
            const QString& alpha3, const QString& delta3, const Structures::Date& dateTime3);
        ~ConcreteMementoForManuallyAngularMeasurementsAndDates();

        bool operator ==(const ConcreteMementoForManuallyAngularMeasurementsAndDates& other) const;

        const QString& GetAlpha1();
        const QString& GetDelta1();
        const Structures::Date& GetDateTime1();
        const QString& GetAlpha2();
        const QString& GetDelta2();
        const Structures::Date& GetDateTime2();
        const QString& GetAlpha3();
        const QString& GetDelta3();
        const Structures::Date& GetDateTime3();
    };
}

