#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include "database.h"
#include "ui_editaccountdialog.h"

class FullAccountDialog:public QDialog
{
    Q_OBJECT
public:
    explicit FullAccountDialog(DataBase * db, QWidget *parent=0);
    ~FullAccountDialog();

private slots:
    void on_buttonBox_accepted();
    void on_pushButtonStreetChoose_clicked();

private:
    DataBase * db;
    Ui::EditAccountDialog ui;
    int streetId;
};

#endif // ACCOUNTDIALOG_H
