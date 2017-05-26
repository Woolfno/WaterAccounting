#include "liststreetdialog.h"
#include "streetdialog.h"

#include <QMessageBox>

#include <QDebug>

ListStreetDialog::ListStreetDialog(DataBase *db, int selectId, QWidget *parent):
    QDialog(parent), db(db), streetId(selectId)
{
    ui.setupUi(this);
    setFixedSize(290, 300);

    model=new QSqlQueryModel(this);
    db->allStreet(model);
    ui.listStreet->setModel(model);
    ui.listStreet->setModelColumn(1);
    if(selectId>0)
    {
        for(int i=0; i< model->rowCount();++i)
        {
            if(selectId==model->index(i, 0).data().toInt())
            {
                ui.listStreet->setCurrentIndex(model->index(i,1));
                break;
            }
        }
    }
}

ListStreetDialog::~ListStreetDialog()
{
    delete model;
}

void ListStreetDialog::on_buttonBox_accepted()
{
    streetId=model->data(model->index(ui.listStreet->currentIndex().row(),0)).toInt();
    streetName=model->data(model->index(ui.listStreet->currentIndex().row(),1)).toString();
    qDebug()<<"List Street select";
    qDebug()<<streetId;
}

QString ListStreetDialog::getStreetName() const
{
    return streetName;
}

void ListStreetDialog::onlyCloseButton() const
{
    ui.buttonBox->setStandardButtons(QDialogButtonBox::Close);
}

int ListStreetDialog::getStreetId() const
{
    return streetId;
}

void ListStreetDialog::on_pushButtonAdd_clicked()
{
    StreetDialog * dlg=new StreetDialog();
    if(dlg->exec()==QDialog::Accepted)
    {
        if(!dlg->getStreetName().isEmpty())
        {
            if(!db->addStreet(dlg->getStreetName()))
                throw "can`t add new street";
            else
            {
                db->allStreet(model);
                qDebug()<<dlg->getStreetName();
            }
        }
    }
    delete dlg;
}

void ListStreetDialog::on_pushButtonDelete_clicked()
{
    int delId=model->data(model->index(ui.listStreet->currentIndex().row(),0)).toInt();
    QString name=model->data(model->index(ui.listStreet->currentIndex().row(),1)).toString();
    QMessageBox acceptMsg("Учет воды", "Вы действительно хотите удалить улицу "+name,
                          QMessageBox::Question,
                          QMessageBox::Yes|QMessageBox::Default,
                          QMessageBox::No|QMessageBox::Escape,
                          QMessageBox::NoButton);
    if(acceptMsg.exec()==QMessageBox::Yes)
    {
        if(!db->deleteStreet(delId))
            qDebug()<<"Error delete street";
        qDebug()<<"Удалить";
        db->allStreet(model);
    }
    else
        qDebug()<<"Не удалять";
}

void ListStreetDialog::on_pushButtonEdit_clicked()
{
    int editId=model->data(model->index(ui.listStreet->currentIndex().row(), 0)).toInt();
    QString editName=model->data(model->index(ui.listStreet->currentIndex().row(), 0)).toString();

    StreetDialog *dlg=new StreetDialog;
    dlg->setStreetName(editName);
    if(dlg->exec()==QDialog::Accepted)
    {
        editName=dlg->getStreetName();
        if(!db->updateStreet(editId, editName))
            qDebug()<<"not edit";
        db->allStreet(model);
    }
}
