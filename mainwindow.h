#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore>
#include <QtSql>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_refresh_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_btn_load_clicked();

    void on_btn_select_2_clicked();

    void on_actionCreate_New_DB_triggered();

    void on_actionConnect_to_Existing_DB_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    QString m_qsDbPath, m_qsBaseDir;

    void setBaseDir(QString path);
    void setDbPath(QString path);
    void openDB();
};

#endif // MAINWINDOW_H
