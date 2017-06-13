#include "tableratedialog.h"
#include "ui_tableratedialog.h"

TableRateDialog::TableRateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableRateDialog)
{
    ui->setupUi(this);
}

TableRateDialog::~TableRateDialog()
{
    delete ui;
}
