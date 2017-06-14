#ifndef TABLERATEDIALOG_H
#define TABLERATEDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

#include "database.h"

namespace Ui {
class TableRateDialog;
}

class TableRateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableRateDialog(DataBase * db, QWidget *parent = 0);
    ~TableRateDialog();

private slots:
    void on_pushButtonAdd_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    DataBase * db;
    Ui::TableRateDialog *ui;
    QSqlTableModel * model;

};

#endif // TABLERATEDIALOG_H
