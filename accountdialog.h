#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include "database.h"
#include "ui_addaccountdialog.h"

class AccountDialog:public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(DataBase * db, int selectId=-1, QWidget *parent=0);
    ~AccountDialog();

    int getAccountId() const;

private slots:
    void on_buttonBox_accepted();

private:
    DataBase * db;
    int accountId;
    Ui::AccountDialog ui;
};

#endif // ACCOUNTDIALOG_H
