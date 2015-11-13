#include "urlgenerator.h"

UrlGenerator::UrlGenerator()
{
    initialize();
}

void UrlGenerator::initialize()
{
    m_qsUrlBase = "http://waterservices.usgs.gov/nwis/";
    m_qsFormat = "rdb";
    m_qsSiteType = "ST";
    m_qsDataType = "iv,dv";
    m_qsParams = "00060,00061";
}

QString UrlGenerator::stateSites(QString state)
{
    QString qsUrl;
    QString abrv = QueryManager::getStateAbbrev(state).toLower();

    qsUrl = m_qsUrlBase + "site/?format=" + m_qsFormat + "&stateCd=" +
            abrv + "&siteType=" + m_qsSiteType + "&hasDataTypeCd=" + m_qsDataType;

    return qsUrl;
}

QString UrlGenerator::siteTimePeriod(int nSite, int nYearS, int nMonthS, int nDayS, int nYearE, int nMonthE, int nDayE, int type)
{
    QString qsType, dateStart, dateEnd, site, qsUrl;
    if (type == 1)
    {
        qsType = "dv/";
    }
    else if (type == 2)
    {
        qsType == "iv/";
    }
    else
    {
        //error
    }

    dateStart = QString::number(nYearS) + "-" + QString::number(nMonthS) + "-" + QString::number(nDayS);
    dateEnd = QString::number(nYearE) + "-" + QString::number(nMonthE) + "-" + QString::number(nDayE);
    site = QString::number(nSite);

    qsUrl = m_qsUrlBase + qsType + "?format=" + m_qsFormat + "&sites=" + site + "&startDT=" + dateStart +
            "&endDT=" + dateEnd + "&parameterCd=" + m_qsParams;

    return qsUrl;
}

QString UrlGenerator::siteTimePeriod(QString site, QString startDate, QString endDate, QString type)
{
    QString qsUrl;
    int nSite = site.toInt();
    site = QString("%1").arg(nSite, 8, 10, QChar('0'));

    qsUrl = m_qsUrlBase + type + "/?format=" + m_qsFormat + "&sites=" + site + "&startDT=" + startDate +
            "&endDT=" + endDate + "&parameterCd=" + m_qsParams;

    qDebug()<<qsUrl;
    return qsUrl;
}

