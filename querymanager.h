#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QtSql>

class QueryManager
{
public:
    QueryManager();

    void CreateAllTables();
    void CreateSitesTable();
    int CreateStatesTable();
    void CreateValuesTable();
    void loadStateData();
};

#endif // QUERYMANAGER_H
