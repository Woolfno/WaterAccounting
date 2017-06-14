#include "accrualsdialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDate>
#include <math.h>

#include "decimal.h"
#include "monthmodel.h"

AccrualsDialog::AccrualsDialog(DataBase * db, QString &buildingId, QWidget *parent):
    QDialog(parent)
{
    ui.setupUi(this);
    setFixedSize(215, 190);

    QSqlQueryModel * model=new QSqlQueryModel(this);
    db->infoForAccurals(model, buildingId);
    qDebug()<<model->query().lastQuery();
    qDebug()<<model->rowCount();
    qDebug()<<model->index(0,0).data().toString();
    ui.lineEditBuildingId->setText(buildingId);
    QString address("ул. %1 д. %2 кв. %3");
    address=address.arg(model->index(0,1).data().toString())
            .arg(model->index(0,2).data().toInt())
            .arg(model->index(0,3).data().toInt());
    ui.lineEditAddress->setText(address);
    int peoples=model->index(0,4).data().toInt();
    ui.lineEditPeoples->setText(QString::number(peoples));
    double rate=model->index(0,5).data().toDouble();
    ammount=rate;
    ammount=ammount*peoples;
    ui.lineEditRate->setText(QString::number(rate));
    ui.lineEditSum->setText(ammount.toString());

    MonthModel * monthModel=new MonthModel(this);
    ui.ComboBox->setModel(monthModel);
    ui.ComboBox->setModelColumn(1);
    ui.ComboBox->setCurrentIndex(QDate::currentDate().month());
}

int64_t AccrualsDialog::getAmmount() const
{
    return ammount.getValue();
}

int AccrualsDialog::getMonth() const
{
    return month;
}

void AccrualsDialog::on_pushButtonAccept_clicked()
{
    int currentIndex=ui.ComboBox->currentIndex();
    month=ui.ComboBox->model()->index(currentIndex,0).data().toInt();
    if(month==-1)
        reject();
    accept();
}

void AccrualsDialog::on_pushButtonReject_clicked()
{
    reject();
}
