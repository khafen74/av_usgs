#include "resample.h"

Resampler::Resampler()
{
    setDayOfYear();
}

Resampler::Resampler(QVector<double> dates, QVector<double> values)
{
    setData(dates, values);
    setDayOfYear();
}

void Resampler::setDates(QVector<double> dates)
{
    m_baseDates = dates;
}

void Resampler::setValues(QVector<double> values)
{
    m_baseValues = values;
}

void Resampler::setData(QVector<double> dates, QVector<double> values)
{
    m_baseDates.clear();
    m_baseValues.clear();
    setDates(dates);
    setValues(values);
}

void Resampler::dailyMax()
{
    clearAll();
    QDateTime datetime1, datetime2;
    QDate date1, date2;
    QTime time(0,0,0,0);
    datetime1 = QDateTime::fromTime_t(m_baseDates[0]);
    date1 = datetime1.date();
    double max = m_baseValues[0];
    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime2 = QDateTime::fromTime_t(m_baseDates[i]);
        date2 = datetime2.date();

        if (date1 == date2)
        {
            if (m_baseValues[i] > max)
            {
                max = m_baseValues[i];
            }
        }
        else
        {
            datetime1.setDate(date1);
            datetime1.setTime(time);
            m_newDates.append(datetime1.toTime_t());
            m_newValues.append(max);
            qDebug()<<date1<<max;
            max = m_baseValues[i];
            date1 = date2;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    qDebug()<<date1<<max;
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(max);
}

void Resampler::dailyMin()
{
    clearAll();
    QDateTime datetime1, datetime2;
    QDate date1, date2;
    QTime time(0,0,0,0);
    datetime1 = QDateTime::fromTime_t(m_baseDates[0]);
    date1 = datetime1.date();
    double min = m_baseValues[0];
    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime2 = QDateTime::fromTime_t(m_baseDates[i]);
        date2 = datetime2.date();

        if (date1 == date2)
        {
            if (m_baseValues[i] < min)
            {
                min = m_baseValues[i];
            }
        }
        else
        {
            datetime1.setDate(date1);
            datetime1.setTime(time);
            m_newDates.append(datetime1.toTime_t());
            m_newValues.append(min);
            qDebug()<<date1<<min;
            min = m_baseValues[i];
            date1 = date2;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    qDebug()<<date1<<min;
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(min);
}

void Resampler::dailyMean()
{
    clearAll();
    QDateTime datetime1, datetime2;
    QDate date1, date2;
    QTime time(0,0,0,0);
    datetime1 = QDateTime::fromTime_t(m_baseDates[0]);
    date1 = datetime1.date();
    double mean, sum = 0.0;
    int count = 0;
    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime2 = QDateTime::fromTime_t(m_baseDates[i]);
        date2 = datetime2.date();

        if (date1 == date2)
        {
            sum += m_baseValues[i];
            count++;
        }
        else
        {
            datetime1.setDate(date1);
            datetime1.setTime(time);
            mean = sum/(count*1.0);
            count = 0;
            sum = 0.0;
            m_newDates.append(datetime1.toTime_t());
            m_newValues.append(mean);
            qDebug()<<date1<<mean;
            date1 = date2;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    mean = sum/(count*1.0);
    qDebug()<<date1<<mean;
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(mean);
}

void Resampler::meanByDay()
{
    clearAll();
    QDateTime datetime;
    int doy, index;
    QVector<double> count(366), sum(366), avg;
    count.fill(0.0);
    sum.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        doy = datetime.date().dayOfYear();
        index = m_dayOfYear.indexOf(doy);
        sum[index]+=m_baseValues[i];
        count[index]+=1.0;
    }
    for (int i=0; i<m_dayOfYear.length(); i++)
    {
        avg.append(sum[i]/count[i]);
    }
}

void Resampler::clearDates()
{
    m_newDates.clear();
}

void Resampler::clearValues()
{
    m_newValues.clear();
}

void Resampler::clearAll()
{
    clearDates();
    clearValues();
}

void Resampler::setDayOfYear()
{
    m_dayOfYear.clear();
    for (int i=0; i<367; i++)
    {
        m_dayOfYear.append(i+1.0);
    }
}

