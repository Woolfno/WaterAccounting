#ifndef LISTSTREETDIALOG_H
#define LISTSTREETDIALOG_H

#include <QSqlQueryModel>
#include <QDialog>
#include "ui_liststreetdialog.h"

#include "database.h"

class ListStreetDialog:public QDialog
{
    Q_OBJECT
public:
    explicit ListStreetDialog(DataBase *db, int selectId=-1, QWidget *parent=0);
    ~ListStreetDialog();

    int getStreetId() const;
    QString getStreetName() const;

    void onlyCloseButton() const;

private slots:
    void on_buttonBox_accepted();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::ListStreetDialog ui;
    QSqlQueryModel * model;
    DataBase *db;

    int streetId;
    QString streetName;
};

#endif // LISTSTREETDIALOG_H
