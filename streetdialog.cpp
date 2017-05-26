#include "streetdialog.h"

StreetDialog::StreetDialog(QWidget *parent):QDialog(parent)
{
    ui.setupUi(this);
    setFixedSize(320, 90);    
}

StreetDialog::~StreetDialog()
{

}

QString StreetDialog::getStreetName() const
{
    return streetName;
}

void StreetDialog::on_pushButtonOk_clicked()
{
    if(!ui.lineEditName->text().isEmpty())
    {
        streetName=ui.lineEditName->text();
        QDialog::accept();
    }
}

void StreetDialog::on_pushButtonCancel_clicked()
{
    QDialog::reject();
}

void StreetDialog::setStreetName(const QString &value)
{
    ui.lineEditName->setText(value);
}
