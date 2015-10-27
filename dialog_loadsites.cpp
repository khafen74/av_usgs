#include "dialog_loadsites.h"
#include "ui_dialog_loadsites.h"

dialog_LoadSites::dialog_LoadSites(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LoadSites)
{
    ui->setupUi(this);
}

dialog_LoadSites::~dialog_LoadSites()
{
    delete ui;
}
