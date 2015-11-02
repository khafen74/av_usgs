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
        qDebug()<<"sites exectuted successfully";
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

void QueryManager::CreateValuesTable()
{

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
        qDebug()<<"reading file "<<filename;
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
}

