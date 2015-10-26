#ifndef DIALOGLOADDATA_H
#define DIALOGLOADDATA_H

#include <QDialog>

namespace Ui {
class DialogLoadData;
}

class DialogLoadData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoadData(QWidget *parent = 0);
    ~DialogLoadData();

private:
    Ui::DialogLoadData *ui;
};

#endif // DIALOGLOADDATA_H
