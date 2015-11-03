#ifndef DIALOG_LOADSITES_H
#define DIALOG_LOADSITES_H

#include <QDialog>
#include <QtGui>
#include <QtSql>
#include "urlgenerator.h"
#include "downloadmanger.h"

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
    void deleteFiles();

private slots:
    void on_btn_ok_clicked();

    void on_btn_close_clicked();

    void on_btn_add_clicked();

    void on_btn_remove_clicked();

    void loadSiteData();

private:
    Ui::dialog_LoadSites *ui;

    QString m_qsBaseDir;
    QStringList m_filenames;
    QStringList m_statenames;
    DownloadManager *dlmanage;
};

#endif // DIALOG_LOADSITES_H
