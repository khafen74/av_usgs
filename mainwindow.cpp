#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    m_db.close();
    delete ui;
}

void MainWindow::plot()
{
    ui->plot_main->addGraph();
    ui->plot_main->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot));
    ui->plot_main->graph(0)->setData(m_plotData[0], m_plotData[1]);
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot_main->xAxis->setAutoTickStep(true);
    ui->plot_main->xAxis->setDateTimeFormat("MM/dd\nyyyy");
    ui->plot_main->xAxis->setRange(m_plotData[0].first()-24*3600, m_plotData[0].last()+24*3600);
    ui->plot_main->yAxis->setRange(50, 100);

    ui->plot_main->replot();
    ui->plot_main->update();
    ui->plot_main->repaint();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString siteno = index.sibling(row, 0).data().toString();
    QString sitename = index.sibling(row, 1).data().toString();
}

void MainWindow::on_btn_load_clicked()
{
    dialog_LoadData dialog(m_qsBaseDir, this);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionCreate_New_DB_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Database as"), "C:/", tr("Discharge DB(*.qdb)"));
    QFileInfo fi(filename);

    if (fi.exists())
    {
        QMessageBox::information(this, "The file already exists", "Please choose another filename");
    }
    else
    {
        setDbPath(filename);
        setBaseDir(fi.absolutePath());
        openDB(true);
    }
}

void MainWindow::on_actionConnect_to_Existing_DB_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Database"), "C:/", tr("Discharge DB(*.qdb)"));
    QFileInfo fi(filename);

    if (!fi.exists())
    {
        QMessageBox::information(this, "The file does not exist", "The selected file does not exist you must select a valid *.qdb file");
    }

    else
    {
        setDbPath(filename);
        setBaseDir(fi.absolutePath());
        openDB(false);
    }
}

void MainWindow::setBaseDir(QString path)
{
    m_qsBaseDir = path;
}

void MainWindow::setDbPath(QString path)
{
    m_qsDbPath = path;
}


void MainWindow::openDB(bool create)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_qsDbPath);

    if (!m_db.open())
    {
        QMessageBox::information(this, "Error", "Problem opening database");
    }
    if (create)
    {
        m_QueryManager.CreateAllTables();
        m_QueryManager.loadStates();
    }
}

void MainWindow::on_btn_select_clicked()
{
    dialog_SelectData dialog(this);
    connect(&dialog, &dialog_SelectData::queriesDone, this, &MainWindow::on_queriesDone);
    connect(&dialog, &dialog_SelectData::siteListReady, this, &MainWindow::on_siteListReady);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_queriesDone(QList<QString> queries)
{
    QSqlQuery query;
    QVector<double> dates, values;

    double value, dateMsecs;

    for (int i=0; i<queries.length(); i++)
    {
        bool good = query.exec(queries[i]);
        if (good)
        {
            while (query.next())
            {
                value = query.value(5).toDouble();
                dateMsecs = query.value(3).toDateTime().toTime_t();
                values.append(value);
                dates.append(dateMsecs);
            }
        }
        else
        {
            qDebug()<<"problem exectuing query "<<queries[i];
        }

        m_baseData.append(dates);
        m_baseData.append(values);
    }

    Resampler resample(m_baseData[0], m_baseData[1]);
    resample.dailyMax();
    resample.dailyMin();
    resample.dailyMean();
}

void MainWindow::on_siteListReady(QList<QString> sites)
{
    m_sites = sites;
}
