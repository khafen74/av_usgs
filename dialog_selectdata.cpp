#include "dialog_selectdata.h"
#include "ui_dialog_selectdata.h"

dialog_SelectData::dialog_SelectData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_SelectData)
{
    ui->setupUi(this);

    showSitesDv();
    showSitesIv();
    setupSelectTable();
}

dialog_SelectData::~dialog_SelectData()
{
    delete ui;
}

void dialog_SelectData::addToSelect(QString valueType)
{
    QModelIndexList selection;

    if (!QString::compare(valueType, "dv"))
    {
        selection = ui->tv_sitesDv->selectionModel()->selectedRows();
    }
    else if (!QString::compare(valueType, "iv"))
    {
        selection  = ui->tv_sitesIv->selectionModel()->selectedRows();
    }

    for (int i=0; i<selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        int row = index.row();
        QString siteno = index.sibling(row, 0).data().toString();
        ui->table_select->insertRow(ui->table_select->rowCount());
        ui->table_select->setItem(ui->table_select->rowCount()-1, 0, new QTableWidgetItem(siteno));
        ui->table_select->setItem(ui->table_select->rowCount()-1, 1, new QTableWidgetItem(valueType));
    }
}

void dialog_SelectData::setEndDate(QString date)
{
    m_qsEndDate = date;
}

void dialog_SelectData::setStartDate(QString date)
{
    m_qsStartDate = date;
}

QList<QString> dialog_SelectData::getQueries()
{
    return m_queries;
}

void dialog_SelectData::on_btn_addDv_clicked()
{
    addToSelect("dv");
}

void dialog_SelectData::on_btn_addIv_clicked()
{
    addToSelect("iv");
}

void dialog_SelectData::on_btn_reset_clicked()
{
    ui->table_select->clear();

    for (int i=0; i<ui->table_select->rowCount(); i++)
    {
        ui->table_select->removeRow(ui->table_select->rowCount()-1);
    }

    setupSelectTable();
}

void dialog_SelectData::showSitesIv()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select distinct siteid from datavalues where valuetype='iv'");
    bool test = query.exec();
    if (!test)
    {
        qDebug()<<"select sites show iv query failed";
    }
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Site ID (instantaneous)"));

    ui->tv_sitesIv->setModel(model);
}

void dialog_SelectData::showSitesDv()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select distinct siteid from datavalues where valuetype='dv'");
    bool test = query.exec();
    if (!test)
    {
        qDebug()<<"select sites show dv query failed";
    }
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Site Id (daily)"));

    ui->tv_sitesDv->setModel(model);
}

void dialog_SelectData::setupSelectTable()
{
    QStringList headers;
    headers << "Site"<<"Type";
    ui->table_select->setColumnCount(2);
    ui->table_select->setHorizontalHeaderLabels(headers);
}

void dialog_SelectData::on_btn_ok_clicked()
{

    setStartDate(QueryManager::dateFromInt(ui->spin_nYearStart->value(), ui->spin_nMonthStart->value(), ui->spin_nDayStart->value()));
    setEndDate(QueryManager::dateFromInt(ui->spin_nYearEnd->value(), ui->spin_nMonthEnd->value(), ui->spin_nDayEnd->value()));
    m_queries.clear();
    m_sites.clear();

    for (int i=0; i<ui->table_select->rowCount(); i++)
    {
        QString query(QueryManager::timeSeriesQuery(ui->table_select->item(i,0)->text(), m_qsStartDate, m_qsEndDate, ui->table_select->item(i,1)->text()));
        m_sites.append(ui->table_select->item(i,0)->text() + " " +ui->table_select->item(i,1)->text());
        m_queries.append(query);
    }

    emit siteListReady(m_sites);
    emit queriesDone(m_queries);

    this->close();
}

void dialog_SelectData::on_btn_cancel_clicked()
{
    this->close();
}
