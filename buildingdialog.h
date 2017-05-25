#ifndef BUILDINGDIALOG_H
#define BUILDINGDIALOG_H
#include <QDialog>
#include "ui_buildingdialog.h"

class BuildingDialog:public QDialog
{
    Q_OBJECT
public:
    explicit BuildingDialog(QWidget *parent=0);
    ~BuildingDialog();

private:
    Ui::BuildingDialog ui;
};

#endif // BUILDINGDIALOG_H
