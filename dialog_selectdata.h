#ifndef DIALOG_SELECTDATA_H
#define DIALOG_SELECTDATA_H

#include <QDialog>
#include "querymanager.h"

namespace Ui {
class dialog_SelectData;
}

class dialog_SelectData : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_SelectData(QWidget *parent = 0);
    ~dialog_SelectData();

   void addToSelect(QString valueType);
   void setEndDate(QString date);
   void setStartDate(QString date);
   QList<QString> getQueries();

private slots:
    void on_btn_addDv_clicked();

    void on_btn_addIv_clicked();

    void on_btn_reset_clicked();
    void showSitesIv();
    void showSitesDv();
    void setupSelectTable();

    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

signals:
    void queriesDone(QList<QString> queries);
    void siteListReady(QList<QString> sites);

private:
    Ui::dialog_SelectData *ui;
    QString m_qsStartDate, m_qsEndDate;
    QList<QString> m_queries, m_sites;
};

#endif // DIALOG_SELECTDATA_H
