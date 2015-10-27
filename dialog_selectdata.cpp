#include "dialog_selectdata.h"
#include "ui_dialog_selectdata.h"

dialog_SelectData::dialog_SelectData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_SelectData)
{
    ui->setupUi(this);
}

dialog_SelectData::~dialog_SelectData()
{
    delete ui;
}
