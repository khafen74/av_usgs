#include "resample.h"

Resampler::Resampler()
{
    init();
}

Resampler::Resampler(QVector<double> dates, QVector<double> values)
{
    setData(dates, values);
    setDayOfYear();
}

QVector<double> Resampler::getResampledDates()
{
    return m_newDates;
}

QVector<double> Resampler::getMinMaxDates(QList<QVector<double> > allDates)
{
    QVector<double> minMax;
    double min, max;
    min = allDates[0][0];
    max = allDates[0][0];
    for (int i=0; i<allDates.length(); i++)
    {
        for (int j=0; j<allDates[i].length(); j++)
        {
            if (allDates[i][j] < min)
            {
                min = allDates[i][j];
            }
            if (allDates[i][j] > max)
            {
                max = allDates[i][j];
            }
        }
    }

    minMax.append(min);
    minMax.append(max);

    return minMax;
}

QVector<double> Resampler::getDays()
{
    QVector<double> days;

    for (int i=0; i<366; i++)
    {
        days.append(i+1);
    }

    return days;
}

QVector<double> Resampler::getMonths()
{
    QVector<double> months;

    for (int i=0; i<12; i++)
    {
        months.append(i+1);
    }

    return months;
}

QVector<double> Resampler::getYears(QList<QVector<double> > allDates)
{
    QVector<double> minMax = getMinMaxDates(allDates);
    QVector<double> years;

    int yearMin = QDateTime::fromTime_t(minMax[0]).date().year();
    int yearMax = QDateTime::fromTime_t(minMax[1]).date().year();

    for (int i=yearMin; i<yearMax+1; i++)
    {
        years.append(i);
    }

    return years;
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

QVector<double> Resampler::dailyMax()
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
            max = m_baseValues[i];
            date1 = date2;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(max);

    return m_newValues;
}

QVector<double> Resampler::dailyMin()
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
            min = m_baseValues[i];
            date1 = date2;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(min);

    return m_newValues;
}

QVector<double> Resampler::dailyMean()
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
            if (count == 0)
            {
                sum += m_baseValues[i];
                count++;
            }
            mean = sum/(count*1.0);
            m_newDates.append(datetime1.toTime_t());
            m_newValues.append(mean);
            date1 = date2;
            count = 0;
            sum = 0.0;
        }
    }

    datetime1.setDate(date1);
    datetime1.setTime(time);
    mean = sum/(count*1.0);
    m_newDates.append(datetime1.toTime_t());
    m_newValues.append(mean);

    return m_newValues;
}

QVector<double> Resampler::meanByDay()
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
    for (int i=0; i<count.length(); i++)
    {
        avg.append(sum[i]/count[i]);
    }

    return avg;
}

QVector<double> Resampler::meanByMonth()
{
    clearAll();
    QDateTime datetime;
    int mon, index;
    QVector<double> count(12), sum(12), avg;
    count.fill(0.0);
    sum.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        mon = datetime.date().month();
        index = m_months.indexOf(mon);
        sum[index]+=m_baseValues[i];
        count[index]+=1.0;
    }
    for (int i=0; i<count.length(); i++)
    {
        avg.append(sum[i]/count[i]);
    }

    return avg;
}

QVector<double> Resampler::meanByYear(QVector<double> years)
{
    clearAll();
    QDateTime datetime;
    int year, index;
    QVector<double> count(years.length()), sum(years.length()), avg;
    count.fill(0.0);
    sum.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        year = datetime.date().year();
        index = years.indexOf(year);
        sum[index]+=m_baseValues[i];
        count[index]+=1.0;
    }
    for (int i=0; i<count.length(); i++)
    {
        avg.append(sum[i]/count[i]);
    }

    return avg;
}

QVector<double> Resampler::maxByDay()
{
    clearAll();
    QDateTime datetime;
    int doy, index;
    QVector<double> max(366);
    max.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        doy = datetime.date().dayOfYear();
        index = m_dayOfYear.indexOf(doy);
        if (m_baseValues[i] > max[index])
        {
            max[index] = m_baseValues[i];
        }
    }

    return max;
}

QVector<double> Resampler::maxByMonth()
{
    clearAll();
    QDateTime datetime;
    int mon, index;
    QVector<double> max(12);
    max.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        mon = datetime.date().month();
        index = m_months.indexOf(mon);
        if (m_baseValues[i] > max[index])
        {
            max[index] = m_baseValues[i];
        }
    }

    return max;
}

QVector<double> Resampler::maxByYear(QVector<double> years)
{
    clearAll();
    QDateTime datetime;
    int year, index;
    QVector<double> max(years.length());
    max.fill(0.0);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        year = datetime.date().year();
        index = years.indexOf(year);
        if (m_baseValues[i] > max[index])
        {
            max[index] = m_baseValues[i];
        }
    }

    return max;
}

QVector<double> Resampler::minByDay()
{
    clearAll();
    QDateTime datetime;
    int doy, index;
    QVector<double> min(366);
    min.fill(99999999999999);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        doy = datetime.date().dayOfYear();
        index = m_dayOfYear.indexOf(doy);
        if (m_baseValues[i] < min[index])
        {
            min[index] = m_baseValues[i];
        }
    }

    for (int i=0; i<min.length(); i++)
    {
        if (min[i] >= 99999999999999)
        {
            min[i] = 0.0;
        }
    }

    return min;
}

QVector<double> Resampler::minByMonth()
{
    clearAll();
    QDateTime datetime;
    int mon, index;
    QVector<double> min(12);
    min.fill(99999999999999);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        mon = datetime.date().month();
        index = m_months.indexOf(mon);
        if (m_baseValues[i] < min[index])
        {
            min[index] = m_baseValues[i];
        }
    }

    for (int i=0; i<min.length(); i++)
    {
        if (min[i] >= 99999999999999)
        {
            min[i] = 0.0;
        }
    }

    return min;
}

QVector<double> Resampler::minByYear(QVector<double> years)
{
    clearAll();
    QDateTime datetime;
    int year, index;
    QVector<double> min(years.length());
    min.fill(99999999999999);

    for (int i=0; i<m_baseDates.length(); i++)
    {
        datetime = QDateTime::fromTime_t(m_baseDates[i]);
        year = datetime.date().year();
        index = years.indexOf(year);
        if (m_baseValues[i] < min[index])
        {
            min[index] = m_baseValues[i];
        }
    }

    for (int i=0; i<min.length(); i++)
    {
        if (min[i] >= 99999999999999)
        {
            min[i] = 0.0;
        }
    }

    return min;
}

void Resampler::init()
{
    setDayOfYear();
    m_months = getMonths();
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

