#include "buildingdialog.h"
#include "listaccountdialog.h"

#include <QDebug>
#include <QSqlQueryModel>

BuildingDialog::BuildingDialog(DataBase *db, QWidget *parent):
    db(db), QDialog(parent), accountId(-1)
{
    ui.setupUi(this);
    setFixedSize(330,270);
    ui.lineEditId->setFocus();

    QSqlQueryModel * streetModel=new QSqlQueryModel(this);
    QSqlQueryModel * rateModel=new QSqlQueryModel(this);

    db->allStreet(streetModel);
    ui.comboBoxStreet->setModel(streetModel);
    ui.comboBoxStreet->setModelColumn(1);

    db->allRate(rateModel);
    ui.comboBoxRate->setModel(rateModel);
    ui.comboBoxRate->setModelColumn(1);
}

BuildingDialog::~BuildingDialog()
{

}

void BuildingDialog::on_pushButton_clicked()
{
    ListAccountDialog * dlg=new ListAccountDialog(db, accountId);
    if(dlg->exec()==QDialog::Accepted)
    {
        ui.lineEditAccountName->setText(dlg->getAccountName());
        accountId=dlg->getAccountId();
    }
    delete dlg;
}

void BuildingDialog::on_buttonBox_accepted()
{
    if(!ui.lineEditId->text().isEmpty() && !ui.lineEditNumber->text().isEmpty())
    {
        QString id=ui.lineEditId->text();
        int streetId=ui.comboBoxStreet->model()->index(ui.comboBoxStreet->currentIndex(), 0).data().toInt();
        int rateId=ui.comboBoxRate->model()->index(ui.comboBoxRate->currentIndex(), 0).data().toInt();
        int numberHose=ui.lineEditNumber->text().toInt();
        int numberOfPeople=ui.lineEditPeople->text().toInt();
        int numberFlat=ui.lineEditFlat->text().toInt();
        qDebug()<<accountId<<streetId<<rateId<<numberHose<<numberOfPeople;

        db->addBuilding(id, accountId, streetId, numberHose, numberFlat, numberOfPeople, rateId);
    }
}
