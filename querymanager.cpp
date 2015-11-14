#include "querymanager.h"

QueryManager::QueryManager()
{

}

QueryManager::~QueryManager()
{

}

void QueryManager::CreateAllTables()
{
    CreateStatesTable();
    CreateSitesTable();
    CreateValuesTable();
}

int QueryManager::CreateSitesTable()
{
    QString query = "CREATE TABLE sites"
            "("
            "SiteId integer primary key"
            ",AgencyID varchar(50)"
            ",SiteName varchar (255)"
            ",SiteType varchar(50)"
            ",Lat double"
            ",Lon double"
            ",CoordAcy varchar(50)"
            ",Datum varchar(50)"
            ",Alt double"
            ",AltAcy double"
            ",AltDatum varchar(50)"
            ",HucID integer"
            ",StateID integer"
            ",foreign key(StateID) references states(stateid)"
            ");";
    QSqlQuery qry;

    if (qry.exec(query))
    {
        return 0;
    }
    else
    {
        qDebug()<<"sites not successful";
        return 1;
    }
}

int QueryManager::CreateStatesTable()
{
    QString query = "CREATE TABLE states"
                    "(stateid integer primary key, "
                    "statename varchar(255));";

    QSqlQuery qry;

    if(qry.exec(query))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int QueryManager::CreateValuesTable()
{
    QString query = "CREATE TABLE datavalues ("
            "ValueID integer primary key,"
            "SiteID integer,"
            "LocalDateTime DATETIME,"
            "UTCDateTime DATETIME,"
            "TimeZoneID VARCHAR(50),"
            "Qvalue DOUBLE,"
            "ValueType VARCHAR(50),"
            "QualityControlLevel VARCHAR(50),"
            "QualityControlLevelID integer);";
    QSqlQuery qry;

    if (qry.exec(query))
    {
        return 0;
    }
    else
    {
        qDebug()<<"datavalues not successful";
        return 1;
    }
}

void QueryManager::loadSite(QStringList list, QString state)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO sites"
                "("
                "SiteID "
                ",AgencyID"
                ",SiteName"
                ",SiteType"
                ",Lat"
                ",Lon"
                ",CoordAcy"
                ",Datum"
                ",Alt"
                ",AltAcy"
                ",AltDatum"
                ",HucID"
                ",StateID"
                ")"
                "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)");

    qry.addBindValue(list[1].toLongLong());
    qry.addBindValue(list[0]);
    qry.addBindValue(list[2]);
    qry.addBindValue(list[3]);
    qry.addBindValue(list[4].toDouble());
    qry.addBindValue(list[5].toDouble());
    qry.addBindValue(list[6]);
    qry.addBindValue(list[7]);
    qry.addBindValue(list[8].toDouble());
    qry.addBindValue(list[9]);
    qry.addBindValue(list[10]);
    qry.addBindValue(list[11].toInt());
    qry.addBindValue(stateNames.indexOf(state)+1);
    qry.exec();
}

void QueryManager::loadStates()
{
    QSqlQuery qry;

    for (int i=0; i<stateNames.length(); i++)
    {
        qry.prepare("INSERT INTO states"
                    "(statename)"
                    "VALUES (?);");

        qry.addBindValue(stateNames[i]);
        qry.exec();
    }
}

void QueryManager::readSitesFile(QString filename, QString state)
{
    QFile inFile(filename);
    if (inFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream inStream(&inFile);
        QString line;
        QStringList list;
        while (!inStream.atEnd())
        {
            line = inStream.readLine();
            list = line.split("\t");
            if (!QString::compare(list[0], "USGS", Qt::CaseInsensitive))
            {
                loadSite(list, state);
            }
        }
        inFile.close();
    }
    else
    {
        //error opening file
        qDebug()<<"error opening file"<<filename;
    }
}

void QueryManager::loadValues(QStringList list, QString site, QString type)
{
    QDateTime local, utc;
    double q;
    int qid;
    QString quality;
    QString offset;

    if (list.length()>5)
    {
        type = "iv";
        offset = list[3];
        local = QDateTime::fromString(list[2], "yyyy-MM-dd hh:mm");
        int offsetUTC = getUTCOffset(offset);
        utc = local.addSecs(offsetUTC*3600);
        quality = list[5];
        q = list[4].toDouble();
        //qDebug()<<"load instant values"<<offset<<local<<utc<<quality<<q;
    }
    else
    {
       type = "dv";
        offset = "None";
        local = QDateTime::fromString(list[2], "yyyy-MM-dd");
        utc = local;
        quality = list[4];
        q = list[3].toDouble();
    }

    qid = getQualityControlLevelID(quality);

    QSqlQuery qry;
    qry.prepare("INSERT INTO datavalues"
                "("
                "SiteID"
                ",LocalDateTime"
                ",UTCDateTime"
                ",TimeZoneID"
                ",Qvalue"
                ",ValueType"
                ",QualityControlLevel"
                ",QualityControlLevelID"
                ")"
                "VALUES (?,?,?,?,?,?,?,?);");

    qry.addBindValue(site.toLongLong());
    qry.addBindValue(local);
    qry.addBindValue(utc);
    qry.addBindValue(offset);
    qry.addBindValue(q);
    qry.addBindValue(type);
    qry.addBindValue(quality);
    qry.addBindValue(qid);
    bool good = qry.exec();

    if (!good)
    {
        qDebug()<<"error loading values"<<qry.executedQuery()<<site.toLongLong()<<q<<type<<quality;
    }
}

void QueryManager::readValues(QString filename, QString type, QString site)
{
    QFile inFile(filename);
    if (inFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream inStream(&inFile);
        QString line;
        QStringList list;

        while (!inStream.atEnd())
        {
            line = inStream.readLine();
            list = line.split("\t");
            if (!QString::compare(list[0], "USGS", Qt::CaseInsensitive))
            {
                loadValues(list, site, type);
            }
        }

        inFile.close();
        qDebug()<<"finished file "<<filename;
    }
    else
    {
        //error opening file
        qDebug()<<"error opening file"<<filename;
    }
}

QString QueryManager::getStateAbbrev(QString stateName)
{
    bool exists = false;

    for (int i=0; i<stateNames.length(); i++)
    {
        if (!QString::compare(stateName, stateNames[i], Qt::CaseInsensitive))
        {
            exists = true;
            return stateAbbrevs[i];
        }
    }

    if (!exists)
    {
        //error
    }
    return 0;
}

int QueryManager::getQualityControlLevelID(QString quality)
{
    if (!QString::compare(quality, "P", Qt::CaseInsensitive))
    {
        return 0;
    }
    else if (!QString::compare(quality, "A", Qt::CaseInsensitive))
    {
        return 1;
    }
    else
    {
        return -9999;
    }
}

int QueryManager::getUTCOffset(QString timeZoneAbbrev)
{
    if (!QString::compare(timeZoneAbbrev, "ADT", Qt::CaseInsensitive))
        return -3;
    else if (!QString::compare(timeZoneAbbrev, "AKDT", Qt::CaseInsensitive))
        return -8;
    else if (!QString::compare(timeZoneAbbrev, "AST", Qt::CaseInsensitive))
        return -4;
    else if (!QString::compare(timeZoneAbbrev, "AKST", Qt::CaseInsensitive))
        return -9;
    else if (!QString::compare(timeZoneAbbrev, "CDT", Qt::CaseInsensitive))
        return -4;
    else if (!QString::compare(timeZoneAbbrev, "CST", Qt::CaseInsensitive))
        return -5;
    else if (!QString::compare(timeZoneAbbrev, "EGT", Qt::CaseInsensitive))
        return -1;
    else if (!QString::compare(timeZoneAbbrev, "EGST", Qt::CaseInsensitive))
        return 0;
    else if (!QString::compare(timeZoneAbbrev, "HADT", Qt::CaseInsensitive))
        return -9;
    else if (!QString::compare(timeZoneAbbrev, "HAST", Qt::CaseInsensitive))
        return -10;
    else if (!QString::compare(timeZoneAbbrev, "HST", Qt::CaseInsensitive))
        return -10;
    else if (!QString::compare(timeZoneAbbrev, "MDT", Qt::CaseInsensitive))
        return -6;
    else if (!QString::compare(timeZoneAbbrev, "MeST", Qt::CaseInsensitive))
        return -8;
    else if (!QString::compare(timeZoneAbbrev, "MST", Qt::CaseInsensitive))
        return -7;
    else if (!QString::compare(timeZoneAbbrev, "MDT", Qt::CaseInsensitive))
        return -7;
    else if (!QString::compare(timeZoneAbbrev, "PST", Qt::CaseInsensitive))
        return -8;
    else if (!QString::compare(timeZoneAbbrev, "PMDT", Qt::CaseInsensitive))
        return -2;
    else if (!QString::compare(timeZoneAbbrev, "PMST", Qt::CaseInsensitive))
        return -3;
    else if (!QString::compare(timeZoneAbbrev, "WGT", Qt::CaseInsensitive))
        return -3;
    else if (!QString::compare(timeZoneAbbrev, "WGST", Qt::CaseInsensitive))
        return -2;
    else
        return -9999;
}

