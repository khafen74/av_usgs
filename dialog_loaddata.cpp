#include "dialog_loaddata.h"
#include "ui_dialog_loaddata.h"

dialog_LoadData::dialog_LoadData(QString baseDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LoadData)
{
    ui->setupUi(this);
    initialize(baseDir);
}

dialog_LoadData::~dialog_LoadData()
{
    delete ui;
}

void dialog_LoadData::initialize(QString baseDir)
{
    m_qsBaseDir = baseDir;

    showSites();
    showStates();
}

void dialog_LoadData::on_btn_loadSites_clicked()
{
    dialog_LoadSites dialog(m_qsBaseDir, this);
    dialog.setModal(true);
    dialog.exec();
}

void dialog_LoadData::on_btn_add_clicked()
{

}

void dialog_LoadData::on_btn_ok_clicked()
{
    this->close();
}

void dialog_LoadData::on_btn_close_clicked()
{
    this->close();
}

void dialog_LoadData::showSites()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select siteid, sitename from sites");
    bool test = query.exec();
    if (!test)
    {
        qDebug()<<"load sites query failed";
    }
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("State Name"));

    ui->tv_sites->setModel(model);
    ui->tv_sites->setColumnWidth(1, 300);
}

void dialog_LoadData::showStates()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select distinct states.statename from states inner join (select sites.stateid from  sites) rTable on states.stateid = rTable.stateid order by states.statename;");
    bool test = query.exec();
    if (!test)
    {
        qDebug()<<"load sites query failed";
    }
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("State Name"));

    ui->tv_states->setModel(model);
}

void dialog_LoadData::updateSites()
{

}

void dialog_LoadData::on_btn_reset_clicked()
{

}

void dialog_LoadData::on_btn_refresh_clicked()
{
    showSites();
    showStates();
}
