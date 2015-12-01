#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot_main->plotLayout()->insertRow(0);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, "Plot Area"));
}

MainWindow::~MainWindow()
{
    m_db.close();
    delete ui;
}

int MainWindow::getPlotValueType()
{
    int value;

    if (ui->rbtn_mean->isChecked())
    {
        value = 0;
    }
    else if (ui->rbtn_min->isChecked())
    {
        value = 1;
    }
    else if (ui->rbtn_max)
    {
        value = 2;
    }
    else
    {
        value = -1;
    }

    return value;
}

void MainWindow::plot()
{
    clearPlot();

    int value = getPlotValueType();

    if (value >= 0)
    {
        if (ui->rbtn_day->isChecked())
        {
            plotDay(value);
        }
        else if (ui->rbtn_month->isChecked())
        {
            plotMonth(value);
        }
        else if (ui->rbtn_year->isChecked())
        {
            plotYear(value);
        }
        else
        {
            QMessageBox::information(this, "Select Plotting Options", "You have not correctly selected plotting options");
        }
    }
    else
    {
        QMessageBox::information(this, "Select Plotting Options", "You have not correctly selected plotting options");
    }
}

void MainWindow::plotDay(int value)
{
    int increment = 3;
    int offset = value;
    QVector<int> red, green, blue;
    red.append(242), red.append(50), red.append(5);
    green.append(12), green.append(12), green.append(245);
    blue.append(24), blue.append(242), blue.append(5);
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot_main->xAxis->setAutoTickStep(true);
    ui->plot_main->xAxis->setDateTimeFormat("MM/dd\nyyyy");
    ui->plot_main->xAxis->setPadding(5);
    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setLabel("Date");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");
    //ui->plot_main->plotLayout()->insertRow(0);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, "Average Daily Discharge"));

    for (int i=0; i<m_dates.length(); i++)
    {
        ui->plot_main->addGraph();
        ui->plot_main->graph(i)->setPen(QPen(QColor(red[i], green[i], blue[i])));
        ui->plot_main->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot_main->graph(i)->setData(m_dates[i], m_daily[offset]);
        ui->plot_main->graph(i)->setName(m_sites[i]);

        offset += increment;
    }

    ui->plot_main->rescaleAxes();
    ui->plot_main->replot();
    ui->plot_main->update();
    ui->plot_main->repaint();
}

void MainWindow::plotMonth(int value)
{
    int nIncrement = 3;
    int nOffset = value;

    QVector<int> red, green, blue;
    red.append(242), red.append(50), red.append(5);
    green.append(12), green.append(12), green.append(245);
    blue.append(24), blue.append(242), blue.append(5);
    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setAutoTickStep(false);
    ui->plot_main->xAxis->setTickStep(1);
    ui->plot_main->xAxis->setSubTickCount(0);
    ui->plot_main->xAxis->setPadding(5);
    //ui->plot_main->plotLayout()->insertRow(0);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, "Average Monthly Discharge"));
    ui->plot_main->xAxis->setLabel("Month");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");

    for (int i=0; i<(m_byMonth.length()/nIncrement); i++)
    {
        ui->plot_main->addGraph();
        ui->plot_main->graph(i)->setPen(QPen(QColor(red[i], green[i], blue[i])));
        ui->plot_main->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot_main->graph(i)->setData(m_months, m_byMonth[nOffset]);
        ui->plot_main->graph(i)->setName(m_sites[i]);

        nOffset += nIncrement;
    }

    ui->plot_main->rescaleAxes();
    ui->plot_main->replot();
    ui->plot_main->update();
    ui->plot_main->repaint();
}

void MainWindow::plotYear(int value)
{
    int nIncrement = 3;
    int nOffset = value;
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

void MainWindow::setupPlotData()
{
    clearPlotData();

    m_days = Resampler::getDays();
    m_months = Resampler::getMonths();
    m_years = Resampler::getYears(m_baseDates);
    m_datesMinMax = Resampler::getMinMaxDates(m_baseDates);

    Resampler Resample;
    for (int i=0; i<m_baseData.length(); i++)
    {
        Resample.setData(m_baseDates[i], m_baseData[i]);
        m_daily.append(Resample.dailyMean());
        m_dates.append(Resample.getResampledDates());
        m_daily.append(Resample.dailyMin());
        m_daily.append(Resample.dailyMax());
        m_byMonth.append(Resample.meanByMonth());
        m_byMonth.append(Resample.minByMonth());
        m_byMonth.append(Resample.maxByMonth());
    }
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

        m_baseDates.append(dates);
        m_baseData.append(values);
        values.clear();
        dates.clear();
    }

    setupPlotData();
}

void MainWindow::on_siteListReady(QList<QString> sites)
{
    m_sites = sites;
}

void MainWindow::clearPlot()
{
    ui->plot_main->clearGraphs();
    ui->plot_main->clearItems();
    ui->plot_main->clearPlottables();
    ui->plot_main->plotLayout()->remove(ui->plot_main->plotLayout()->element(0,0));
}

void MainWindow::clearPlotData()
{
    m_dates.clear();
    m_daily.clear();
    m_byDay.clear();
    m_byMonth.clear();
    m_byYear.clear();
    m_months.clear();
    m_days.clear();
    m_months.clear();
    m_years.clear();
    m_datesMinMax.clear();
}

void MainWindow::on_btn_plot_clicked()
{
    plot();
}
