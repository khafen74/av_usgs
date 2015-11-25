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

    void setDates(QVector<double> dates);
    void setValues(QVector<double> values);
    void setData(QVector<double> dates, QVector<double> values);

    void dailyMax();
    void dailyMin();
    void dailyMean();
    void meanByDay();
    void meanByMonth();
    void meanByYear();
    void maxByDay();
    void maxByMonth();
    void maxByYear();
    void minByDay();
    void minByMonth();
    void minByYear();

private:
    QVector<double> m_baseDates, m_baseValues, m_dayOfYear;
    QVector<double> m_newDates, m_newValues;
    QList< QVector<double> > m_daily, m_byDay, m_byMonth, m_byYear;

    void clearDates();
    void clearValues();
    void clearAll();
    void setDayOfYear();
};

#endif // RESAMPLE_H
