#ifndef DIALOGSELECTDATA_H
#define DIALOGSELECTDATA_H

#include <QDialog>

namespace Ui {
class DialogSelectData;
}

class DialogSelectData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectData(QWidget *parent = 0);
    ~DialogSelectData();

private:
    Ui::DialogSelectData *ui;
};

#endif // DIALOGSELECTDATA_H
