#include "buildingdialog.h"

BuildingDialog::BuildingDialog(QWidget *parent):
    QDialog(parent)
{
    ui.setupUi(this);
    setFixedSize(355,240);
}

BuildingDialog::~BuildingDialog()
{

}
