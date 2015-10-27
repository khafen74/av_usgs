#include "dialog_loaddata.h"
#include "ui_dialog_loaddata.h"

dialog_LoadData::dialog_LoadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LoadData)
{
    ui->setupUi(this);
}

dialog_LoadData::~dialog_LoadData()
{
    delete ui;
}

void dialog_LoadData::on_btn_loadSites_clicked()
{
    dialog_LoadSites dialog(this);
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
