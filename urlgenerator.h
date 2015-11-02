#ifndef URLGENERATOR_H
#define URLGENERATOR_H

#include <QUrl>
#include <QtCore>
#include "querymanager.h"


class UrlGenerator
{
public:
    UrlGenerator();

    void initialize();
    QString stateSites(QString state);
    QString siteTimePeriod(int nSite, int nYearS, int nMonthS, int nDayS, int nYearE, int nMonthE, int nDayE, int type);

private:
    QString m_qsUrlBase;
    QString m_qsFormat;
    QString m_qsSiteType;
    QString m_qsDataType;
    QString m_qsParams;

};

#endif // URLGENERATOR_H
