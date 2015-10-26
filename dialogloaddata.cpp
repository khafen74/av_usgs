#include "dialogloaddata.h"
#include "ui_dialogloaddata.h"

DialogLoadData::DialogLoadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoadData)
{
    ui->setupUi(this);
}

DialogLoadData::~DialogLoadData()
{
    delete ui;
}
