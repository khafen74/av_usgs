#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("database.db");

    if (mydb.open())
    {
        qDebug()<<"db open";

        QSqlQuery qry;
        if (qry.exec("CREATE TABLE sites "
                     "(siteid integer primary key, "
                     "agency varchar(10), "
                     "siteno int, "
                     "sitename varchar(255), "
                     "sitetype varchar(10), "
                     "latitude double, "
                     "longitude double, "
                     "latlongacc varchar(10), "
                     "datum varchar(10), "
                     "elevation double, "
                     "elevationacc varchar(3), "
                     "verticaldatum varchar(10), "
                     "huc int)"))
        {
            qDebug()<<"query complete";
        }
        else
        {
            qDebug()<<"query failed";
        }
    }
    else
    {
        qDebug()<<"db failed to open";
    }

    QFile inFile("text.txt");
    if (inFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&inFile);
        QString line;
        QStringList list;
        QSqlQuery query;

        int count = 0;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            qDebug()<<list.length()<<list;
            list = line.split("\t");
            query.prepare("INSERT INTO sites ("
                          "agency"
                          ",siteno"
                          ",sitename"
                          ",sitetype"
                          ",latitude"
                          ",longitude"
                          ",latlongacc"
                          ",datum"
                          ",elevation"
                          ",elevationacc"
                          ",verticaldatum"
                          ",huc"
                          ") "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(list[0]);
            query.addBindValue(list[1].toInt());
            query.addBindValue(list[2]);
            query.addBindValue(list[3]);
            query.addBindValue(list[4].toDouble());
            query.addBindValue(list[5].toDouble());
            query.addBindValue(list[6]);
            query.addBindValue(list[7]);
            query.addBindValue(list[8].toDouble());
            query.addBindValue(list[9]);
            query.addBindValue(list[10]);
            query.addBindValue(list[11].toInt());
            query.exec();
            count++;
            //qDebug()<<"added row "<<count;
        }
    }
    else
    {
        qDebug()<<"error opening file";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_refresh_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();
    QSqlQueryModel *model3 = new QSqlQueryModel();

    QSqlQuery *query = new QSqlQuery(mydb);
    QSqlQuery *query2 = new QSqlQuery(mydb);
    QSqlQuery *query3 = new QSqlQuery(mydb);

    query->prepare("select sitename from sites");
    query->exec();
    query2->prepare("select siteno from sites");
    query2->exec();
    query3->prepare("select siteno, sitename from sites");
    query3->exec();
    model->setQuery(*query);
    model2->setQuery(*query2);
    model3->setQuery(*query3);

    ui->lv_names->setModel(model);
    ui->lv_number->setModel(model2);
    ui->tableView->setModel(model3);
}
