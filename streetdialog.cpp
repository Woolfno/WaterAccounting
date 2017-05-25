#include "streetdialog.h"

StreetDialog::StreetDialog(QWidget *parent):QDialog(parent), valid(false)
{
    ui.setupUi(this);
    setFixedSize(320, 90);    
}

StreetDialog::~StreetDialog()
{

}

void StreetDialog::on_buttonBox_accepted()
{
    if(!ui.lineEditName->text().isEmpty())
    {
        streetName=ui.lineEditName->text();
        valid=true;
        return;
    }
    QDialog::reject();
}

QString StreetDialog::getStreetName() const
{
    return streetName;
}

void StreetDialog::closeEvent(QCloseEvent *event)
{
    if(valid)
        event->accept();
    else
        event->ignore();
}
