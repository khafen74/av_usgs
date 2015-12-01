#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setColors();
    ui->plot_main->plotLayout()->insertRow(0);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, "Plot Area"));
}

MainWindow::~MainWindow()
{
    m_db.close();
    delete ui;
}

QString MainWindow::getPlotValueString(int value)
{
    QString str;

    if (value == 0)
    {
        str = "Average";
    }
    else if (value == 1)
    {
        str = "Minimum";
    }
    else if (value == 2)
    {
        str = "Maximum";
    }
    else
    {
        str = QString::null;
    }

    return str;
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
    else if (ui->rbtn_max->isChecked())
    {
        value = 2;
    }
    else if (ui->rbtn_doy->isChecked())
    {
        value = 3;
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
    QString str = getPlotValueString(value);

    if (value >= 0)
    {
        if (ui->rbtn_day->isChecked())
        {
            plotDay(value, str);
        }
        else if (ui->rbtn_month->isChecked())
        {
            plotMonth(value, str);
        }
        else if (ui->rbtn_year->isChecked())
        {
            plotYear(value, str);
        }
        else if (ui->rbtn_doy->isChecked())
        {
            plotDayOfYear(value, str);
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

void MainWindow::plotDay(int value, QString valStr)
{
    int increment = 3;
    int offset = value;
    int maxIterations = m_dates.length();
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot_main->xAxis->setAutoTickStep(true);
    ui->plot_main->xAxis->setDateTimeFormat("MM/dd\nyyyy");
    ui->plot_main->xAxis->setPadding(5);
    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setLabel("Date");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, valStr + " Discharge (Daily)"));

    if (m_dates.length() > 10)
    {
        maxIterations = 10;
    }

    for (int i=0; i<maxIterations; i++)
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

void MainWindow::plotDayOfYear(int value, QString valStr)
{
    int nIncrement = 3;
    int nOffset = value;
    int maxIterations = m_dates.length();

    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->plot_main->xAxis->setAutoTickStep(false);
    ui->plot_main->xAxis->setTickStep(10);
    ui->plot_main->xAxis->setSubTickCount(1);
    ui->plot_main->xAxis->setPadding(5);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, valStr + " Discharge (By Day of Year)"));
    ui->plot_main->xAxis->setLabel("Day of Year");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");

    if (m_dates.length() > 10)
    {
        maxIterations = 10;
    }

    for (int i=0; i<maxIterations; i++)
    {
        ui->plot_main->addGraph();
        ui->plot_main->graph(i)->setPen(QPen(QColor(red[i], green[i], blue[i])));
        ui->plot_main->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot_main->graph(i)->setData(m_days, m_byDay[nOffset]);
        ui->plot_main->graph(i)->setName(m_sites[i]);

        nOffset += nIncrement;
    }

    ui->plot_main->rescaleAxes();
    ui->plot_main->replot();
    ui->plot_main->update();
    ui->plot_main->repaint();
}

void MainWindow::plotMonth(int value, QString valStr)
{
    int nIncrement = 3;
    int nOffset = value;
    int maxIterations = m_dates.length();

    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->plot_main->xAxis->setAutoTickStep(false);
    ui->plot_main->xAxis->setTickStep(1);
    ui->plot_main->xAxis->setSubTickCount(0);
    ui->plot_main->xAxis->setPadding(5);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, valStr + " Discharge (By Month)"));
    ui->plot_main->xAxis->setLabel("Month");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");

    if (m_dates.length() > 10)
    {
        maxIterations = 10;
    }

    for (int i=0; i<maxIterations; i++)
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

void MainWindow::plotYear(int value, QString valStr)
{
    int nIncrement = 3;
    int nOffset = value;
    int maxIterations = m_dates.length();

    ui->plot_main->legend->setVisible(true);
    ui->plot_main->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->plot_main->xAxis->setAutoTickStep(false);
    ui->plot_main->xAxis->setTickStep(1);
    ui->plot_main->xAxis->setSubTickCount(0);
    ui->plot_main->xAxis->setPadding(5);
    ui->plot_main->plotLayout()->addElement(0,0,new QCPPlotTitle(ui->plot_main, valStr + " Discharge (By Year)"));
    ui->plot_main->xAxis->setLabel("Month");
    ui->plot_main->yAxis->setLabel("Discharge (cms)");

    if (m_dates.length() > 10)
    {
        maxIterations = 10;
    }

    for (int i=0; i<maxIterations; i++)
    {
        ui->plot_main->addGraph();
        ui->plot_main->graph(i)->setPen(QPen(QColor(red[i], green[i], blue[i])));
        ui->plot_main->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot_main->graph(i)->setData(m_years, m_byYear[nOffset]);
        ui->plot_main->graph(i)->setName(m_sites[i]);

        nOffset += nIncrement;
    }

    ui->plot_main->rescaleAxes();
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

void MainWindow::setColors()
{
    red.append(242), red.append(50), red.append(5), red.append(0), red.append(250), red.append(250), red.append(2), red.append(238), red.append(62), red.append(156);
    green.append(12), green.append(12), green.append(245), green.append(0), green.append(155), green.append(246), green.append(250), green.append(2), green.append(148), green.append(25);
    blue.append(24), blue.append(242), blue.append(5), blue.append(0), blue.append(2), blue.append(2), blue.append(246), blue.append(250), blue.append(59), blue.append(31);
}

void MainWindow::setDbPath(QString path)
{
    m_qsDbPath = path;
}

void MainWindow::setupPlotData()
{
    clearPlot();
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
        m_byDay.append(Resample.meanByDay());
        m_byDay.append(Resample.minByDay());
        m_byDay.append(Resample.maxByDay());
        m_byYear.append(Resample.meanByYear(m_years));
        m_byYear.append(Resample.minByYear(m_years));
        m_byYear.append(Resample.maxByYear(m_years));
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

    m_baseDates.clear();
    m_baseData.clear();

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
    ui->plot_main->replot();
    ui->plot_main->update();
    ui->plot_main->repaint();
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
