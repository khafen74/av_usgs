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
