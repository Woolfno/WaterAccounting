#include "ratedialog.h"
#include <QLineEdit>

RateDialog::RateDialog(DataBase *db, QWidget *parent):
    db(db), QDialog(parent)
{
    ui.setupUi(this);
    setFixedSize(200, 100);
//    ui.lineEditRate->setValidator(new QDoubleValidator(0, 1000, 2));
}

void RateDialog::on_buttonBox_accepted()
{
    if(ui.lineEditRate->text().length()>0)
    {
        if(!db->addRate(ui.lineEditRate->text().toDouble()))
             throw "can`t add new account";
    }

}
