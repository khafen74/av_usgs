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
    setupLoadTable();
}

void dialog_LoadData::setupLoadTable()
{
    QStringList headers;
    headers << "Site" << "StartDate" << "EndDate"<<"Type";
    ui->table_load->setColumnCount(4);
    ui->table_load->setHorizontalHeaderLabels(headers);
}

void dialog_LoadData::on_btn_loadSites_clicked()
{
    dialog_LoadSites dialog(m_qsBaseDir, this);
    dialog.setModal(true);
    dialog.exec();
}

void dialog_LoadData::on_btn_add_clicked()
{
    if (!ui->line_siteNo->text().isNull() && !ui->line_siteNo->text().isEmpty() && (ui->rbtn_day->isChecked() || ui->rbtn_inst->isChecked()))
    {
        QString type;
        if (ui->rbtn_day->isChecked())
        {
            type = "dv";
        }
        else
        {
            type = "iv";
        }

        QString startDate = QString::number(ui->spin_nYearStart->value()) + "-" + QString::number(ui->spin_nMonthStart->value()) + "-" + QString::number(ui->spin_nDayStart->value());
        QString endDate = QString::number(ui->spin_nYearEnd->value()) + "-" + QString::number(ui->spin_nMonthEnd->value()) + "-" + QString::number(ui->spin_nDayEnd->value());
        ui->table_load->insertRow(ui->table_load->rowCount());
        ui->table_load->setItem(ui->table_load->rowCount()-1, 0, new QTableWidgetItem(ui->line_siteNo->text()));
        ui->table_load->setItem(ui->table_load->rowCount()-1, 1, new QTableWidgetItem(startDate));
        ui->table_load->setItem(ui->table_load->rowCount()-1, 2, new QTableWidgetItem(endDate));
        ui->table_load->setItem(ui->table_load->rowCount()-1, 3, new QTableWidgetItem(type));
    }
}

void dialog_LoadData::on_btn_ok_clicked()
{
    QStringList urls;
    UrlGenerator UrlGen;
    QString site, start, end, type;

    for (int i=0; i<ui->table_load->rowCount(); i++)
    {
        site = ui->table_load->item(i,0)->text();
        start = ui->table_load->item(i,1)->text();
        end = ui->table_load->item(i,2)->text();
        type = ui->table_load->item(i,3)->text();
        m_type.append(type);
        m_site.append(site);
        urls.append(UrlGen.siteTimePeriod(site, start, end, type));
    }
    dlmanage = new DownloadManager();
    connect(dlmanage, SIGNAL(done()), SLOT(loadDataValues()));
    dlmanage->setBasePath(m_qsBaseDir);
    dlmanage->execute(urls);
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
    for (int i=0; i<ui->table_load->rowCount(); i++)
    {
        ui->table_load->removeRow(i);
    }
    showSites();
    showStates();
}

void dialog_LoadData::on_btn_refresh_clicked()
{
    showSites();
    showStates();
}

void dialog_LoadData::on_tv_sites_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString siteno = index.sibling(row, 0).data().toString();
    ui->line_siteNo->setText(siteno);
}

void dialog_LoadData::loadDataValues()
{
    qDebug()<<"url download done";

    QueryManager QryManage;
    m_filenames = dlmanage->getFilenames();

    for (int i=0; i<m_filenames.length(); i++)
    {
        qDebug()<<"reading file"<<m_filenames[i]<<m_filenames.length()<<m_type.length()<<m_site.length();
        QryManage.readValues(m_filenames[i], m_type[i], m_site[i]);
    }

    ui->table_load->clear();
    deleteFiles();
    this->close();
}

void dialog_LoadData::deleteFiles()
{
    for (int i=0; i<m_filenames.length(); i++)
    {
        QFile file(m_filenames[i]);
        file.remove();
    }
}
