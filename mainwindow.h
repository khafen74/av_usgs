#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore>
#include <QtSql>
#include <iostream>
#include "querymanager.h"
#include "dialog_loaddata.h"
#include "dialog_selectdata.h"
#include "resample.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void plot();

private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_btn_load_clicked();

    void on_actionCreate_New_DB_triggered();

    void on_actionConnect_to_Existing_DB_triggered();

    void on_btn_select_clicked();

public slots:

    void on_queriesDone(QList<QString> queries);
    void on_siteListReady(QList<QString> sites);

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    QString m_qsDbPath;
    QString m_qsBaseDir;
    QueryManager m_QueryManager;
    QList< QVector<double> > m_baseData, m_plotData;
    QList<QString> m_sites;

    void setBaseDir(QString path);
    void setDbPath(QString path);
    void openDB(bool create);
};

#endif // MAINWINDOW_H
