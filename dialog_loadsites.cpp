#include "dialog_loadsites.h"
#include "ui_dialog_loadsites.h"

dialog_LoadSites::dialog_LoadSites(QString baseDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LoadSites)
{
    ui->setupUi(this);
    initialize(baseDir);
}

dialog_LoadSites::~dialog_LoadSites()
{
    delete ui;
}

void dialog_LoadSites::on_btn_ok_clicked()
{
    QStringList urls;
    UrlGenerator UrlGen;

    qDebug()<<ui->list_add->count();
    for (int i=0; i<ui->list_add->count(); i++)
    {
        QListWidgetItem *item = ui->list_add->item(i);
        qDebug()<<item->text();
        urls.append(UrlGen.stateSites(item->text()));
    }
    DownloadManager *manager = new DownloadManager();
    manager->setBasePath(m_qsBaseDir);
    manager->execute(urls);

    ui->list_add->clear();

    this->close();
}

void dialog_LoadSites::on_btn_close_clicked()
{
    this->close();
}

void dialog_LoadSites::initialize(QString baseDir)
{
    m_qsBaseDir = baseDir;

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;

    query.prepare("select statename from states");
    query.exec();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("State Name"));

    ui->tv_states->setModel(model);
}

void dialog_LoadSites::on_btn_add_clicked()
{
    QModelIndexList select = ui->tv_states->selectionModel()->selectedRows();

    for (int i=0; i<select.count(); i++)
    {
        QModelIndex index = select.at(i);
        int row = index.row();
        QString state = index.sibling(row, 0).data().toString();
        int newRow = ui->list_add->row(ui->list_add->currentItem());
        ui->list_add->insertItem(newRow, state);
    }
    ui->list_add->sortItems(Qt::AscendingOrder);
}

void dialog_LoadSites::on_btn_remove_clicked()
{
    QList<QListWidgetItem*> items = ui->list_add->selectedItems();

    for (int i=0; i<items.length(); i++)
    {
        ui->list_add->takeItem(ui->list_add->row(items[i]));
    }
}
