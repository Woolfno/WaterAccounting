#ifndef RATEDIALOG_H
#define RATEDIALOG_H

#include <QDialog>

#include "database.h"
#include "ui_addratedialog.h"

class RateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RateDialog(DataBase * db, QWidget * parent=0);

private slots:
    void on_buttonBox_accepted();

private:
    DataBase * db;
    Ui::AddRateDialog ui;
};

#endif // RATEDIALOG_H
