#include "querymanager.h"

QueryManager::QueryManager()
{

}

void QueryManager::CreateAllTables()
{
    CreateStatesTable();
    CreateSitesTable();
    CreateValuesTable();
}

void QueryManager::CreateSitesTable()
{

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

void QueryManager::loadStateData()
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

QString QueryManager::getStateAbbrev(QString stateName)
{
    bool exists = false;

    for (int i=0; i<stateNames.length(); i++)
    {
        if (QString::compare(stateName, stateNames[i], Qt::CaseInsensitive))
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

