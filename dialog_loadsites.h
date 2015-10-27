#ifndef DIALOG_LOADSITES_H
#define DIALOG_LOADSITES_H

#include <QDialog>

namespace Ui {
class dialog_LoadSites;
}

class dialog_LoadSites : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LoadSites(QWidget *parent = 0);
    ~dialog_LoadSites();

private:
    Ui::dialog_LoadSites *ui;
};

#endif // DIALOG_LOADSITES_H
