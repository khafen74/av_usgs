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

private:
    QString m_qsUrlBase;
    QString m_qsFormat;
    QString m_qsSiteType;
    QString m_qsDataType;

};

#endif // URLGENERATOR_H
