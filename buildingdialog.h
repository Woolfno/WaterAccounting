#ifndef BUILDINGDIALOG_H
#define BUILDINGDIALOG_H
#include <QDialog>
#include "ui_buildingdialog.h"

#include "database.h"

class BuildingDialog:public QDialog
{
    Q_OBJECT
public:
    explicit BuildingDialog(DataBase * db, QWidget *parent=0);
    ~BuildingDialog();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    DataBase * db;
    int accountId;

    Ui::BuildingDialog ui;
};

#endif // BUILDINGDIALOG_H
