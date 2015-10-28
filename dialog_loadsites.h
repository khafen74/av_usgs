#ifndef DIALOG_LOADSITES_H
#define DIALOG_LOADSITES_H

#include <QDialog>
#include <QtGui>
#include <QtSql>
#include "urlgenerator.h"
#include "downloadmanger.h"
#include "urldownloader.h"

namespace Ui {
class dialog_LoadSites;
}

class dialog_LoadSites : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LoadSites(QString baseDir, QWidget *parent = 0);
    ~dialog_LoadSites();

    void initialize(QString baseDir);

private slots:
    void on_btn_ok_clicked();

    void on_btn_close_clicked();

    void on_btn_add_clicked();

    void on_btn_remove_clicked();

private:
    Ui::dialog_LoadSites *ui;

    QString m_qsBaseDir;
};

#endif // DIALOG_LOADSITES_H
