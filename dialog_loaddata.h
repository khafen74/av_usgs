#ifndef DIALOG_LOADDATA_H
#define DIALOG_LOADDATA_H

#include <QDialog>

namespace Ui {
class dialog_LoadData;
}

class dialog_LoadData : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LoadData(QWidget *parent = 0);
    ~dialog_LoadData();

private:
    Ui::dialog_LoadData *ui;
};

#endif // DIALOG_LOADDATA_H
