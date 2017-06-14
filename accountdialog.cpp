#include "accountdialog.h"

#include <QMessageBox>
#include <QDebug>

#include "liststreetdialog.h"

AccountDialog::AccountDialog(DataBase *db, int selectId, QWidget *parent):
    QDialog(parent), db(db), accountId(selectId)
{
    ui.setupUi(this);
    setFixedSize(350,135);

    if(selectId!=-1)
    {
        QSqlQueryModel model;
        if(db->accountById(&model, accountId))
        {
            ui.lineEditFirstName->setText(model.index(0,0).data().toString());
            ui.lineEditSecondName->setText(model.index(0,1).data().toString());
            ui.lineEditLastName->setText(model.index(0,2).data().toString());
        }
    }
}

AccountDialog::~AccountDialog()
{

}

void AccountDialog::on_buttonBox_accepted()
{
    QString fname=ui.lineEditFirstName->text();
    QString sname=ui.lineEditSecondName->text();
    QString lname=ui.lineEditLastName->text();

    if(!fname.isEmpty() && !sname.isEmpty() && !lname.isEmpty())
    {
        if(accountId!=-1)
        {
            qDebug()<<"Изменить имя ?";
            QMessageBox msg("Учет Воды", "Вы уверены, что хотите изменить?",
                            QMessageBox::Question,
                            QMessageBox::Yes|QMessageBox::Default,
                            QMessageBox::No|QMessageBox::Escape,
                            QMessageBox::NoButton);
            if(msg.exec()==QMessageBox::Yes)
                db->updateAccount(accountId, fname, sname, lname);
        }
        else
            accountId=db->addAccount(fname, sname, lname);
    }
}

int AccountDialog::getAccountId() const
{
    return accountId;
}
