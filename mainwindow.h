#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Меню
    void on_action_add_building_triggered();
    void on_action_list_street_triggered();
    void on_action_list_account_triggered();
    void on_action_accruals_massive_triggered();
    void on_action_accruals_triggered();
    void on_action_list_rate_triggered();
    //-------------------

    void on_treeViewStreet_clicked(const QModelIndex &index);
    void on_tableViewMain_clicked(const QModelIndex &index);
    void on_treeViewOrganization_clicked(const QModelIndex &index);

    void on_pushButtonSearch_clicked();

private:
    Ui::MainWindow *ui;

    DataBase * db;
    QSqlQueryModel * accountModel;
    QSqlQueryModel * populationStreetModel;
    QSqlQueryModel * organizationStreetModel;
    QSqlQueryModel * accrualsModel; //начисления
    QSqlQueryModel * paymentModel; // платеж
    void refreshAccrualsTable(QString buildingId);
};

#endif // MAINWINDOW_H
