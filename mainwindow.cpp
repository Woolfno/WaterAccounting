#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "buildingdialog.h"
#include "liststreetdialog.h"
#include "listaccountdialog.h"
#include "tableratedialog.h"
#include "accrualsdialog.h"
#include "decimal.h"

#include <QList>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    db=new DataBase;
    if(!db->connect())
    {
        qDebug()<<"Error can`t connect to database";
    }
    else{
        accountModel=new QSqlQueryModel(this);
        db->accountByStreetId(accountModel, 1);
        db->accountSetHeader(accountModel);
        ui->tableViewMain->setModel(accountModel);
        ui->tableViewMain->resizeColumnsToContents();
        ui->tableViewMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableViewMain->setColumnHidden(0, true);

        populationStreetModel=new QSqlQueryModel(this);
        db->allStreet(populationStreetModel);
        ui->treeViewStreet->setModel(populationStreetModel);
        ui->treeViewStreet->setHeaderHidden(true);
        ui->treeViewStreet->setColumnHidden(0, true);

        organizationStreetModel=new QSqlQueryModel(this);
        db->allStreet(organizationStreetModel);
        ui->treeViewOrganization->setModel(organizationStreetModel);
        ui->treeViewOrganization->setHeaderHidden(true);
        ui->treeViewOrganization->setColumnHidden(0, true);

        accrualsModel=new QSqlQueryModel(this);
        db->initAccrualModel(accrualsModel);
        ui->tableViewAccruals->setModel(accrualsModel);

        paymentModel=new QSqlQueryModel(this);
        db->initPaymentModel(paymentModel);
        ui->tableViewPayment->setModel(paymentModel);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Меню
void MainWindow::on_action_add_building_triggered()
{
    BuildingDialog *dlg=new BuildingDialog(db, this);
    if(dlg->exec()==QDialog::Accepted)
        qDebug()<<"Accept";
    delete dlg;
}

void MainWindow::on_action_list_street_triggered()
{
    ListStreetDialog * dlg=new ListStreetDialog(db);
    dlg->onlyCloseButton();
    dlg->exec();
    delete dlg;
    db->allStreet(populationStreetModel);
}

void MainWindow::on_action_list_account_triggered()
{
    ListAccountDialog * dlg=new ListAccountDialog(db);
    dlg->exec();
    delete dlg;
}

void MainWindow::on_action_accruals_massive_triggered()
{
    QList<QString> listId=db->allBuildingId();
    int currentMonth=QDate::currentDate().month();
    for(auto iter=listId.begin(); iter!=listId.end(); ++iter)
    {
        int rateId=db->getRateIdByBuilding(*iter);
        if(rateId>0)
        {
            QSqlQueryModel infoAccuralModel;
            db->infoForAccurals(&infoAccuralModel, *iter);
            int peoples=infoAccuralModel.index(0,4).data().toInt();
            double rate=infoAccuralModel.index(0,5).data().toDouble();
            Decimal ammount(rate);
            ammount=ammount*peoples;
            qDebug()<<QString("%1 %2 %3 %4").arg(*iter).arg(rateId).arg(ammount.toString()).arg(currentMonth);
            if(db->addAccural(*iter, rateId, ammount.getValue(), currentMonth))
                qDebug()<<"Successfully";
            else
                qDebug()<<"Error";
        }
    }
}

void MainWindow::on_action_accruals_triggered()
{
    QString buildingId=accountModel->index(ui->tableViewMain->currentIndex().row(),1).data().toString();
    if(!buildingId.isEmpty())
    {
        AccrualsDialog * dlg=new AccrualsDialog(db, buildingId);
        if(dlg->exec()==QDialog::Accepted)
        {
            qDebug()<<"Accepted";
            int rateId=db->getRateIdByBuilding(buildingId);
            if(rateId>0)
            {
                db->addAccural(buildingId, rateId, dlg->getAmmount(), dlg->getMonth());
                refreshAccrualsTable(buildingId);
            }
            else
                qDebug()<<"RateId <0";
        }
        delete dlg;
    }
}

void MainWindow::on_action_list_rate_triggered()
{
    TableRateDialog * dlg=new TableRateDialog(db);
    if(dlg->exec()==QDialog::Accepted)
    {
        qDebug()<<"Accept table rate";
    }
    delete dlg;
}
//-------------------------

void MainWindow::on_tableViewMain_clicked(const QModelIndex &index)
{
    QString buildingId=index.model()->data(index.model()->index(index.row(),1)).toString();
    qDebug()<<buildingId;
    refreshAccrualsTable(buildingId);
    db->paymentByAccountId(paymentModel, buildingId);
}

void MainWindow::on_treeViewStreet_clicked(const QModelIndex &index)
{
    int id=index.model()->data(index.model()->index(index.row(), 0)).toInt();
    db->accountByStreetId(accountModel, id);
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QList<int> listId=db->accountSearch(ui->lineEditSearch->text());
    db->accountByListId(accountModel, listId);
}

void MainWindow::refreshAccrualsTable(QString buildingId)
{
    db->accrualsByBuildingId(accrualsModel, buildingId);
}

void MainWindow::on_treeViewOrganization_clicked(const QModelIndex &index)
{
    int id=index.model()->data(index.model()->index(index.row(), 0)).toInt();
    db->organizationByStreetId(accountModel, id);
}
