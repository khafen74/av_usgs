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
}

void dialog_LoadData::on_btn_loadSites_clicked()
{
    dialog_LoadSites dialog(m_qsBaseDir, this);
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
