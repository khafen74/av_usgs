#ifndef RESAMPLE_H
#define RESAMPLE_H

#include <QtCore>

class Resampler
{
public:
    Resampler();
    Resampler(QVector<double> dates, QVector<double> values);

    QVector<double> getResampledDates();
    QVector<double> getResampledValues();

    static QVector<double> getMinMaxDates(QList< QVector<double> > allDates);
    static QVector<double> getDays();
    static QVector<double> getMonths();
    static QVector<double> getYears(QList<QVector<double> > allDates);
    void setDates(QVector<double> dates);
    void setValues(QVector<double> values);
    void setData(QVector<double> dates, QVector<double> values);

    QVector<double> dailyMax();
    QVector<double> dailyMin();
    QVector<double> dailyMean();
    QVector<double> meanByDay();
    QVector<double> meanByMonth();
    QVector<double> meanByYear(QVector<double> years);
    QVector<double> maxByDay();
    QVector<double> maxByMonth();
    QVector<double> maxByYear(QVector<double> years);
    QVector<double> minByDay();
    QVector<double> minByMonth();
    QVector<double> minByYear(QVector<double> years);

private:
    QVector<double> m_baseDates, m_baseValues, m_dayOfYear, m_months;
    QVector<double> m_newDates, m_newValues;
    QList< QVector<double> > m_daily, m_byDay, m_byMonth, m_byYear;

    void init();
    void clearDates();
    void clearValues();
    void clearAll();
    void setDayOfYear();
};

#endif // RESAMPLE_H
