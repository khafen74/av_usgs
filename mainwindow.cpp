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
    qDebug()<<"refresh clicked";

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("select siteno, sitename from sites");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Site Number"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Site Name"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(1, 300);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString siteno = index.sibling(row, 0).data().toString();
    QString sitename = index.sibling(row, 1).data().toString();
}

void MainWindow::on_btn_load_clicked()
{

}

void MainWindow::on_btn_select_2_clicked()
{

}
