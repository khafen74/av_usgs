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
}

QUrl UrlGenerator::stateSites(QString state)
{
    QString qsUrl;
    QString abrv = QueryManager::getStateAbbrev(state).toLower();

    qsUrl = m_qsUrlBase + "site/?format=" + m_qsFormat + "&stateCd=" +
            abrv + "&siteType=" + m_qsSiteType + "&hasDataTypeCd=" + m_qsDataType;

    QUrl url(qsUrl);
    return url;
}

