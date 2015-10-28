#ifndef DIALOG_LOADSITES_H
#define DIALOG_LOADSITES_H

#include <QDialog>
#include <QtGui>
#include <QtSql>

namespace Ui {
class dialog_LoadSites;
}

class dialog_LoadSites : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LoadSites(QWidget *parent = 0);
    ~dialog_LoadSites();

private slots:
    void on_btn_ok_clicked();

    void on_btn_close_clicked();

    void on_btn_add_clicked();

private:
    Ui::dialog_LoadSites *ui;

    void initialize();
};

#endif // DIALOG_LOADSITES_H
