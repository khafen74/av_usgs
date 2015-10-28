#include "dialog_loadsites.h"
#include "ui_dialog_loadsites.h"

dialog_LoadSites::dialog_LoadSites(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LoadSites)
{
    ui->setupUi(this);
    initialize();
}

dialog_LoadSites::~dialog_LoadSites()
{
    delete ui;
}

void dialog_LoadSites::on_btn_ok_clicked()
{
    this->close();
}

void dialog_LoadSites::on_btn_close_clicked()
{
    this->close();
}

void dialog_LoadSites::initialize()
{
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
        qDebug()<<state;
        ui->list_add->insertItem(ui->list_add->currentRow(), state);
    }

//    int row = index.row();
//    QString siteno = index.sibling(row, 0).data().toString();
//    QString sitename = index.sibling(row, 1).data().toString();
}
