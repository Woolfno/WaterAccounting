#include "editaccountdialog.h"

#include <QMessageBox>
#include <QDebug>

#include "liststreetdialog.h"

FullAccountDialog::FullAccountDialog(DataBase *db, QWidget *parent):
    db(db), QDialog(parent), streetId(-1)
{
    ui.setupUi(this);
    setFixedSize(350,225);

    QSqlQueryModel * rateModel=new QSqlQueryModel(this);
    db->allRate(rateModel);
    ui.comboBoxRate->setModel(rateModel);
    ui.comboBoxRate->setModelColumn(1);
}

FullAccountDialog::~FullAccountDialog()
{

}

void FullAccountDialog::on_buttonBox_accepted()
{
    QString fname=ui.lineEditFirstName->text();
    QString sname=ui.lineEditSecondName->text();
    QString lname=ui.lineEditLastName->text();
    if(!ui.lineEditNumberHouse->text().isEmpty() && !ui.lineEditFlat->text().isEmpty())
    {
        int numberHouse=ui.lineEditNumberHouse->text().toInt();
        int numberFlat=ui.lineEditFlat->text().toInt();
        if(fname.length()>0 && sname.length()>0 && lname.length()>0)
        {
            int buildingId=db->getBuildingId(streetId, numberHouse, numberFlat);
            if(buildingId!=-1)
            {
                qDebug()<<"Сменить владельца?";
                QMessageBox msg("Учет Воды", "Сменить владельца здания?",
                                QMessageBox::Question,
                                QMessageBox::Yes|QMessageBox::Default,
                                QMessageBox::No|QMessageBox::Escape,
                                QMessageBox::NoButton);
                if(msg.exec()==QMessageBox::Yes)
                {
                    int ownerId=db->addAccount(fname, sname, lname);
                    db->changeBuildingOwen(ownerId, buildingId);
                }
            }
            else
            {
                /*int ownerId=db->addAccount(fname, sname, lname);
                if(ownerId!=-1)*/
                {
                    qDebug()<<"Add new building";
                }
                /*else
                    throw "can`t add new account";
*/
            }
        }
    }
}

void FullAccountDialog::on_pushButtonStreetChoose_clicked()
{
    ListStreetDialog * dlg=new ListStreetDialog(db, streetId);
    if(dlg->exec()==QDialog::Accepted)
    {
        streetId=dlg->getStreetId();
        ui.lineEdit->setText(dlg->getStreetName());
    }
    delete dlg;
}
