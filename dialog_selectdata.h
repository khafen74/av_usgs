#ifndef DIALOG_SELECTDATA_H
#define DIALOG_SELECTDATA_H

#include <QDialog>

namespace Ui {
class dialog_SelectData;
}

class dialog_SelectData : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_SelectData(QWidget *parent = 0);
    ~dialog_SelectData();

private:
    Ui::dialog_SelectData *ui;
};

#endif // DIALOG_SELECTDATA_H
