#include "accountdialog.h"

#include <QDebug>
#include "liststreetdialog.h"

AccountDialog::AccountDialog(DataBase *db, QWidget *parent):
    db(db), QDialog(parent), streetId(-1)
{
    ui.setupUi(this);
    setFixedSize(330,200);
}

AccountDialog::~AccountDialog()
{

}

void AccountDialog::on_buttonBox_accepted()
{
    QString fname=ui.lineEditFirstName->text();
    QString sname=ui.lineEditSecondName->text();
    QString lname=ui.lineEditLastName->text();
    if(fname.length()>0 && sname.length()>0 && lname.length()>0)
    {
        if(!db->addAccount(fname, sname, lname))
            throw "can`t add new account";
    }
}

void AccountDialog::on_pushButtonStreetChoose_clicked()
{
    ListStreetDialog * dlg=new ListStreetDialog(db, streetId);
    if(dlg->exec()==QDialog::Accepted)
    {
        streetId=dlg->getStreetId();
        ui.lineEdit->setText(dlg->getStreetName());
    }
    delete dlg;
}
