#ifndef LISTACCOUNTDIALOG_H
#define LISTACCOUNTDIALOG_H

#include <QSqlQueryModel>
#include <QDialog>
#include "ui_listaccountdialog.h"

#include "database.h"

class ListAccountDialog:public QDialog
{
    Q_OBJECT
public:
    explicit ListAccountDialog(DataBase *db, int selectId=-1, QWidget *parent=0);
    ~ListAccountDialog();

    int getAccountId() const;
    QString getAccountName() const;

    void onlyCloseButton() const;

private slots:
    void on_buttonBox_accepted();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonEdit_clicked();

    void on_lineEditSearch_textEdited(const QString &arg1);

private:
    DataBase *db;
    int accountId;
    QString accountName;
    QSqlQueryModel * model;

    Ui::ListAccountDialog ui;

    void select(int selectId);
};

#endif // LISTACCOUNTDIALOG_H
