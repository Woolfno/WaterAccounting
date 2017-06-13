#include "listaccountdialog.h"
#include "accountdialog.h"

#include <QDialogButtonBox>
#include <QModelIndex>
#include <QDebug>

void ListAccountDialog::select(int selectId)
{
    for(int i=0; i<model->rowCount(); ++i)
    {
        if(selectId==model->index(i,0).data().toInt())
        {
            ui.listAccount->setCurrentIndex(model->index(i,1));
            break;
        }
    }
}

ListAccountDialog::ListAccountDialog(DataBase *db, int selectId, QWidget *parent):
    db(db), accountId(selectId), QDialog(parent)
{
    ui.setupUi(this);
    setFixedSize(290, 300);

    model=new QSqlQueryModel;
    db->allAccounts(model, true);
    ui.listAccount->setModel(model);
    ui.listAccount->setModelColumn(1);
    if(selectId>0)
        select(selectId);
}

ListAccountDialog::~ListAccountDialog()
{
    delete model;
}

int ListAccountDialog::getAccountId() const
{
    return accountId;
}

QString ListAccountDialog::getAccountName() const
{
    return accountName;
}

void ListAccountDialog::onlyCloseButton() const
{
    ui.buttonBox->setStandardButtons(QDialogButtonBox::Close);
}

void ListAccountDialog::on_buttonBox_accepted()
{
    accountId=model->index(ui.listAccount->currentIndex().row(), 0).data().toInt();
    accountName=model->index(ui.listAccount->currentIndex().row(), 1).data().toString();
}

void ListAccountDialog::on_pushButtonAdd_clicked()
{
    AccountDialog * dlg=new AccountDialog(db);
    if(dlg->exec()==QDialog::Accepted)
    {
        db->allAccounts(model, true);
        select(dlg->getAccountId());
    }
    delete dlg;
}

void ListAccountDialog::on_pushButtonDelete_clicked()
{

}

void ListAccountDialog::on_pushButtonEdit_clicked()
{
    accountId=model->index(ui.listAccount->currentIndex().row(), 0).data().toInt();
    if(accountId>0)
    {
        AccountDialog * dlg=new AccountDialog(db);
        if(dlg->exec()==QDialog::Accepted)
        {
            db->allAccounts(model, true);
            select(dlg->getAccountId());
        }
        delete dlg;
    }
}

void ListAccountDialog::on_lineEditSearch_textEdited(const QString &arg1)
{
    if(arg1.length()>3)
    {
        QList<int> list=db->accountSearch(arg1);
        db->accountByListIdName(model, list);
    }
    else if(arg1.length()==0)
        db->allAccounts(model, true);
}
