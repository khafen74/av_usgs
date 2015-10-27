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
