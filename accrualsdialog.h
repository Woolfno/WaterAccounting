#ifndef ACCRUALSDIALOG_H
#define ACCRUALSDIALOG_H

#include <QDialog>
#include "ui_accrualsdialog.h"
#include "database.h"
#include "decimal.h"

class AccrualsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccrualsDialog(DataBase * db, QString &buildingId, QWidget *parent=0);

    int64_t getAmmount() const;
    int getMonth() const;

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonReject_clicked();

private:
    Ui::AccrualsDialog ui;

    int rateId;
    int month;
    Decimal ammount;
};

#endif // ACCRUALSDIALOG_H
