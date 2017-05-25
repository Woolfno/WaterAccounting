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
    void on_action_add_building_triggered();

    void on_action_add_street_triggered();

    void on_listViewStreet_clicked(const QModelIndex &index);

    void on_tableViewMain_clicked(const QModelIndex &index);

    void on_action_add_account_triggered();

    void on_action_add_rate_triggered();

    void on_action_list_street_triggered();

private:
    Ui::MainWindow *ui;

    DataBase * db;
    QSqlQueryModel * accountModel;
    QSqlQueryModel * streetModel;
    QSqlQueryModel * accrualsModel; //начисления
    QSqlQueryModel * paymentModel; // платеж

};

#endif // MAINWINDOW_H
