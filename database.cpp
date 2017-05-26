#include "database.h"
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::connect()
{
    if(QFile(DATABASE_NAME).exists())
    {
        m_db=QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("water.db");

        if(m_db.open())
            return true;
    }
    return false;
}

void DataBase::accountSetHeader(QSqlQueryModel *model)
{
    model->setHeaderData(1, Qt::Horizontal, "№ дома");
    model->setHeaderData(2, Qt::Horizontal, "№ квартиры");
    model->setHeaderData(3, Qt::Horizontal, "Фамилия");
    model->setHeaderData(4, Qt::Horizontal, "Имя");
    model->setHeaderData(5, Qt::Horizontal, "Отчество");
}

void DataBase::accountByStreetId(QSqlQueryModel *model, int id)
{
    QString query="select "
                  "account.id, "
                  "building.number, "
                  "building.number_flat, "
                  "account.first_name, "
                  "account.second_name, "
                  "account.last_name "
                  "from building join account on building.owner=account.id "
                  "where building.street=%1 "
                  "order by building.number;";
    model->query().clear();
    model->setQuery(query.arg(id));
}

void DataBase::allStreet(QSqlQueryModel *model)
{
    model->setQuery("select id, name from street order by name;");
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
    }
}

bool DataBase::addStreet(QString name)
{
    QSqlQuery query;
    query.prepare("insert into street(name) values (?);");
    query.addBindValue(name);
    return query.exec();
}

bool DataBase::deleteStreet(int streetId)
{
    QSqlQuery query;
    query.prepare("delete from street where id=?;");
    query.addBindValue(streetId);
    return query.exec();
}

bool DataBase::updateStreet(int streetId, QString streetName)
{
    QSqlQuery query;
    query.prepare("update street set name=? where id=?;");
    query.addBindValue(streetName);
    query.addBindValue(streetId);
    return query.exec();
}

void DataBase::initAccrualModel(QSqlQueryModel *model)
{
    model->setQuery("select date, rate, amount from accruals limit 0");
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return;
    }
    accrualsSetHeader(model);
}

void DataBase::accrualsSetHeader(QSqlQueryModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Тариф");
    model->setHeaderData(2, Qt::Horizontal, "Сумма");
}

void DataBase::accrualsByAccountId(QSqlQueryModel *model, int id)
{
    QString query="select "
                  "date, rate, amount "
                  "from accruals "
                  "where building=(select id from building where owner=%1);";
    model->query().clear();
    model->setQuery(query.arg(id));
}

bool DataBase::addAccount(QString &firstName, QString &secondName, QString &lastName)
{
    QSqlQuery query;
    query.prepare("insert into account (first_name, second_name, last_name) values (?, ?, ?);");
    query.addBindValue(firstName);
    query.addBindValue(secondName);
    query.addBindValue(lastName);
    return query.exec();
}

void DataBase::initPaymentModel(QSqlQueryModel *model)
{
    model->setQuery("select date, amount from payment limit 0");
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return;
    }
    paymentSetHeader(model);
}

void DataBase::paymentSetHeader(QSqlQueryModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Сумма");
}

void DataBase::paymentByAccountId(QSqlQueryModel *model, int id)
{
    QString query="select "
                  "date, amount "
                  "from payment "
                  "where building=(select id from building where owner=%1)";
    model->query().clear();
    model->setQuery(query.arg(id));
}

bool DataBase::addRate(double value)
{
    QSqlQuery query;
    query.prepare("insert into rate (value) values (?);");
    query.addBindValue(value);
    return query.exec();
}
