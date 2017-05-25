#include "liststreetdialog.h"
#include "streetdialog.h"

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
