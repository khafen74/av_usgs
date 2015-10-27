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
    QList<QString> stateNames;
    stateNames << "Alabama" << "Alaska" << "Arizona" << "Arkansas" << "California" << "Colorado" << "Connecticut"
                              << "Delaware" << "District Of Columbia" << "Florida" << "Georgia" << "Hawaii" << "Idaho" << "Illinois"
                              << "Indiana" << "Iowa" << "Kansas" << "Kentucky" << "Louisiana" << "Maine" << "Maryland" << "Massachusetts"
                              << "Michigan" << "Minnesota" << "Mississippi" << "Missouri" << "Montana" << "Nebraska" << "Nevada"
                              << "New Hampshire" << "New Jersey" << "New Mexico" << "New York" << "North Carolina" << "North Dakota"
                              << "Ohio" << "Oklahoma" << "Oregon" << "Pennsylvania" << "Rhode Island" << "South Carolina"
                              << "South Dakota" << "Tennessee" << "Texas" << "Utah" << "Vermont" << "Virginia"
                              << "Washington" << "West Virginia" << "Wisconsin" << "Wyoming";

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

