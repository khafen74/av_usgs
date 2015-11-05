#ifndef DIALOG_LOADDATA_H
#define DIALOG_LOADDATA_H

#include <QDialog>
#include "dialog_loadsites.h"

namespace Ui {
class dialog_LoadData;
}

class dialog_LoadData : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LoadData(QString baseDir, QWidget *parent = 0);
    ~dialog_LoadData();

    void initialize(QString baseDir);
    void setupLoadTable();

private slots:
    void on_btn_loadSites_clicked();

    void on_btn_add_clicked();

    void on_btn_ok_clicked();

    void on_btn_close_clicked();

    void showSites();
    void showStates();
    void updateSites();
    void on_btn_reset_clicked();

    void on_btn_refresh_clicked();

private:
    Ui::dialog_LoadData *ui;

    QString m_qsBaseDir;
};

#endif // DIALOG_LOADDATA_H
