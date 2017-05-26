#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "buildingdialog.h"
#include "streetdialog.h"
#include "accountdialog.h"
#include "ratedialog.h"
#include "liststreetdialog.h"

#include <QSqlQuery>
#include <QMessageBox>

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

        streetModel=new QSqlQueryModel(this);
        db->allStreet(streetModel);
        ui->listViewStreet->setModel(streetModel);
        ui->listViewStreet->setModelColumn(1);

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

void MainWindow::on_action_add_building_triggered()
{
    BuildingDialog *dlg=new BuildingDialog(this);
    if(dlg->exec()==QDialog::Accepted)
        qDebug()<<"Accept";
    delete dlg;
}

void MainWindow::on_action_add_street_triggered()
{
    StreetDialog * dlg=new StreetDialog(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        qDebug()<<"Add street accept";
        if(!db->addStreet(dlg->getStreetName()))
        {
            QMessageBox msg;
            msg.setText("Невозможно добавить");
            msg.show();
        }
        else
        {
            db->allStreet(streetModel);
        }
    }
    delete dlg;
}

void MainWindow::on_listViewStreet_clicked(const QModelIndex &index)
{
    int id=index.model()->data(index.model()->index(index.row(),0)).toInt();
    qDebug()<<index.data().toString();
    qDebug()<<id;
    db->accountByStreetId(accountModel, id);
}

void MainWindow::on_tableViewMain_clicked(const QModelIndex &index)
{
    int id=index.model()->data(index.model()->index(index.row(),0)).toInt();
    qDebug()<<id;
    db->accrualsByAccountId(accrualsModel, id);
    db->paymentByAccountId(paymentModel, id);
}

void MainWindow::on_action_add_account_triggered()
{
    AccountDialog * dlg=new AccountDialog(db, this);
    if(dlg->exec()==QDialog::Accepted)
        qDebug()<<"Add account";
    delete dlg;
}

void MainWindow::on_action_add_rate_triggered()
{
    RateDialog * dlg=new RateDialog(db, this);
    if(dlg->exec()==QDialog::Accepted)
        qDebug()<<"Add account";
    delete dlg;
}

void MainWindow::on_action_list_street_triggered()
{
    ListStreetDialog * dlg=new ListStreetDialog(db);
    dlg->onlyCloseButton();
    dlg->exec();
    delete dlg;
}
