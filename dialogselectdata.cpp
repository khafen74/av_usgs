#include "dialogselectdata.h"
#include "ui_dialogselectdata.h"

DialogSelectData::DialogSelectData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectData)
{
    ui->setupUi(this);
}

DialogSelectData::~DialogSelectData()
{
    delete ui;
}
