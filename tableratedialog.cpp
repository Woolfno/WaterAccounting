#include "tableratedialog.h"
#include "ui_tableratedialog.h"

#include "ratedialog.h"
#include "datedelegate.h"
#include <QItemDelegate>
#include <QDebug>

TableRateDialog::TableRateDialog(DataBase *db, QWidget *parent) :
    db(db), ui(new Ui::TableRateDialog), QDialog(parent)
{
    ui->setupUi(this);

    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    db->initRate(model);
    db->setRateTableHeader(model);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setItemDelegateForColumn(3, new DateDelegate(this));
}

TableRateDialog::~TableRateDialog()
{
    delete ui;
}

void TableRateDialog::on_pushButtonAdd_clicked()
{
    /*RateDialog * dlg=new RateDialog(db, this);
    if(dlg->exec()==QDialog::Accepted)
    {
        db->initRate(model);
        qDebug()<<"Add rate";
    }
    delete dlg;*/
    model->insertRow(model->rowCount());
}

void TableRateDialog::on_buttonBox_accepted()
{
    model->submitAll();
}

void TableRateDialog::on_buttonBox_rejected()
{
    model->revertAll();
}
