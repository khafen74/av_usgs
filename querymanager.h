#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QtSql>

const QList<QString> stateNames  = QList<QString>()<< "Alabama" << "Alaska" << "Arizona" << "Arkansas" << "California" << "Colorado" << "Connecticut"
                          << "Delaware" << "District Of Columbia" << "Florida" << "Georgia" << "Hawaii" << "Idaho" << "Illinois"
                          << "Indiana" << "Iowa" << "Kansas" << "Kentucky" << "Louisiana" << "Maine" << "Maryland" << "Massachusetts"
                          << "Michigan" << "Minnesota" << "Mississippi" << "Missouri" << "Montana" << "Nebraska" << "Nevada"
                          << "New Hampshire" << "New Jersey" << "New Mexico" << "New York" << "North Carolina" << "North Dakota"
                          << "Ohio" << "Oklahoma" << "Oregon" << "Pennsylvania" << "Rhode Island" << "South Carolina"
                          << "South Dakota" << "Tennessee" << "Texas" << "Utah" << "Vermont" << "Virginia"
                          << "Washington" << "West Virginia" << "Wisconsin" << "Wyoming";
const QList<QString> stateAbbrevs  = QList<QString>()<<"AL"<<"AK"<<"AZ"<<"AR"<<"CA"<<"CO"<<"CT"<<"DE"<<"DC"<<"FL"<<"GA"<<"HI"<<"ID"<<"IL"
                                                    <<"IN"<<"IA"<<"KS"<<"KY"<<"LA"<<"ME"<<"MD"<<"MA"<<"MI"<<"MN"<<"MS"<<"MO"<<"MT"
                                                    <<"NE"<<"NV"<<"NH"<<"NJ"<<"NM"<<"NY"<<"NC"<<"ND"<<"OH"<<"OK"<<"OR"<<"PA"<<"RI"<<"SC"
                                                    <<"SD"<<"TN"<<"TX"<<"UT"<<"VT"<<"VA"<<"WA"<<"WV"<<"WI"<<"WY";

class QueryManager
{
public:
    QueryManager();
    ~QueryManager();

    void CreateAllTables();
    int CreateSitesTable();
    int CreateStatesTable();
    int CreateValuesTable();
    void loadSite(QStringList list, QString state);
    void loadStates();
    void readSitesFile(QString filename, QString state);
    void loadValues(QStringList list, QString site, QString type);
    void readValues(QString filename, QString type, QString site);

    static QString dateFromInt(int year, int month, int day);
    static QString getStateAbbrev(QString stateName);
    static int getQualityControlLevelID(QString quality);
    static QString timeSeriesQuery(QString siteno, QString startDate, QString endDate, QString valueType);
    static int getUTCOffset(QString timeZoneAbbrev);
};

#endif // QUERYMANAGER_H
