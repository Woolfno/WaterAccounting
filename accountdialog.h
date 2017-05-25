#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include "database.h"
#include "ui_addaccountdialog.h"

class AccountDialog:public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(DataBase * db, QWidget *parent=0);
    ~AccountDialog();

private slots:
    void on_buttonBox_accepted();
    void on_pushButtonStreetChoose_clicked();

private:
    Ui::AccountDialog ui;
    DataBase * db;
    int streetId;
};

#endif // ACCOUNTDIALOG_H
