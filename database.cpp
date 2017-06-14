#include "database.h"
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDate>

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
    model->setHeaderData(1, Qt::Horizontal, "Счет");
    model->setHeaderData(2, Qt::Horizontal, "№ дома");
    model->setHeaderData(3, Qt::Horizontal, "№ квартиры");
    model->setHeaderData(4, Qt::Horizontal, "Фамилия");
    model->setHeaderData(5, Qt::Horizontal, "Имя");
    model->setHeaderData(6, Qt::Horizontal, "Отчество");
}

void DataBase::accountByStreetId(QSqlQueryModel *model, int id)
{
    QString query="select "
            "account.id, "
            "building.id, "
            "building.number, "
            "building.number_flat, "
            "account.first_name, "
            "account.second_name, "
            "account.last_name "
            "from building "
            "inner join owner on owner.building = building.id "
            "inner join account on owner.account=account.id "
            "where building.street=%1 "
            "order by building.number;";
    model->query().clear();
    model->setQuery(query.arg(id));
}

void DataBase::organizationByStreetId(QSqlQueryModel *model, int id)
{
    QString query="select "
                  "account.id, "
                  "building.id, "
                  "building.number, "
                  "building.number_flat, "
                  "account.first_name, "
                  "account.second_name, "
                  "account.last_name "
                  "from building "
                  "inner join owner on owner.building = building.id "
                  "inner join account on owner.account=account.id "
                  "where building.category='ORG' and building.street=%1 "
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
    model->setQuery("select date, month, rate, ammount from accruals limit 0");
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
    model->setHeaderData(1, Qt::Horizontal, "Месяц");
    model->setHeaderData(2, Qt::Horizontal, "Тариф");
    model->setHeaderData(3, Qt::Horizontal, "Сумма");
}

void DataBase::accrualsByBuildingId(QSqlQueryModel *model, QString & id)
{
    QString query="select accruals.date, month, rate.per_cube, accruals.ammount/100.0 "
                  "from accruals "
                  "inner join rate on accruals.rate=rate.id "
                  "where accruals.building='%1' ORDER BY date DESC;";
    model->query().clear();
    model->setQuery(query.arg(id));
}

bool DataBase::addAccural(QString buildingId, int rateId, int64_t ammount, int month)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accruals ( "
                    "date, "
                    "building, "
                    "rate, "
                    "month, "
                    "ammount ) "
                    "VALUES ( "
                    ":date, "
                    ":building, "
                    ":rate, "
                    ":month, "
                    ":ammount);");
    query.bindValue(":date", QDate::currentDate().toString("dd.MM.yyyy"));
    query.bindValue(":building", buildingId);
    query.bindValue(":rate", rateId);
    query.bindValue(":month", month);
    query.bindValue(":ammount", ammount);    
    if(query.exec())
        return true;
    qDebug()<<query.lastError().text();
    return false;
}

int DataBase::addAccount(QString &firstName, QString &secondName, QString &lastName)
{
    QSqlQuery query;
    query.prepare("insert into account (first_name, second_name, last_name) values (?, ?, ?);");
    query.addBindValue(firstName);
    query.addBindValue(secondName);
    query.addBindValue(lastName);
    return query.exec() ? query.lastInsertId().toInt() : -1;
}

bool DataBase::accountById(QSqlQueryModel *model, int id)
{
    QString query="SELECT first_name, second_name, last_name FROM account WHERE id= ? ;";
    model->setQuery(query.arg(id));
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateAccount(int id, const QString &fname, const QString &sname, const QString &lname)
{
    QSqlQuery query;
    query.prepare("UPDATE account SET "
                  "first_name = ?, "
                  "second_name = ?, "
                  "last_name = ? "
                  "WHERE id = ?;");
    query.addBindValue(fname);
    query.addBindValue(sname);
    query.addBindValue(lname);
    query.addBindValue(id);
    return query.exec();
}

bool DataBase::changeBuildingOwen(int ownerId, int buildingId)
{
    QSqlQuery query;
    query.prepare("update building set owner=? where id=?;");
    query.addBindValue(ownerId);
    query.addBindValue(buildingId);
    return query.exec();
}

bool DataBase::addAccountWithHouse(QString &firstName, QString &secondName, QString &lastName, int streetId, int numberHouse)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("insert into account (first_name, second_name, last_name) values (?, ?, ?);");
    query.addBindValue(firstName);
    query.addBindValue(secondName);
    query.addBindValue(lastName);
    int ownerId=query.lastInsertId().toInt();
    query.prepare("update building set owner=? where street=? and number=?;");
    query.addBindValue(ownerId);
    query.addBindValue(streetId);
    query.addBindValue(numberHouse);
    query.exec();
    return QSqlDatabase::database().commit();
}

bool DataBase::allAccounts(QSqlQueryModel *model, bool concatName)
{
    if(concatName)
        model->setQuery("select id, first_name || ' ' || second_name || ' ' || last_name from account "
                        "order by first_name, second_name, last_name;");
    else
        model->setQuery("select id, first_name, second_name, last_name from account "
                        "order by first_name, second_name, last_name;");
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return false;
    }
    return true;
}

void DataBase::accountByListId(QSqlQueryModel *model, QList<int> &listId)
{
    QString strId;
    int i=0;
    for(auto iter=listId.begin(); iter!=listId.end(); ++iter, ++i)
    {
        strId.append(QString::number(*iter));
        if(i!=listId.size()-1)
            strId.append(",");
    }

    QString query="select "
            "account.id, "
            "building.number, "
            "building.number_flat, "
            "account.first_name, "
            "account.second_name, "
            "account.last_name "
            "from building "
            "inner join owner on owner.building = building.id "
            "inner join account on owner.account=account.id "
            "where account.id in (%1)"
            "order by building.number ";
    model->query().clear();
    model->setQuery(query.arg(strId));
}

void DataBase::accountByListIdName(QSqlQueryModel *model, QList<int> &listId)
{
    QString strId;
    int i=0;
    for(auto iter=listId.begin(); iter!=listId.end(); ++iter, ++i)
    {
        strId.append(QString::number(*iter));
        if(i!=listId.size()-1)
            strId.append(",");
    }

    QString query="select "
            "account.id, "
            "account.first_name || ' ' "
            "|| account.second_name || ' ' "
            "|| account.last_name "
            "from account "
            "where account.id in (%1)"
            "order by account.first_name;";
    model->query().clear();
    model->setQuery(query.arg(strId));
}

QList<int> DataBase::accountSearch(const QString &pattern)
{
    QSqlQuery query;
    query.prepare("select id "
                  "from account "
                  "where (first_name || ' ' || second_name || ' ' || last_name) like :param;");
    query.bindValue(":param", "%"+pattern+"%");
    if(query.exec())
        qDebug()<<query.lastQuery();
    QList<int> ids;
    while(query.next())
    {
        ids.append(query.value(0).toInt());
    }
    return ids;
}

int DataBase::getBuildingId(int streetId, int numberHouse, int numberFlat, bool hasOwner)
{
    QSqlQuery query;
    if(hasOwner)
        query.prepare("select id from building where street=? and number=? and number_flat=? and owner is NOT NULL;");
    else
        query.prepare("select id from building where street=? and number=? and number_flat=? and owner is NULL;");

    query.addBindValue(streetId);
    query.addBindValue(numberHouse);
    query.addBindValue(numberFlat);
    query.exec();
    int size=-1;
    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::QuerySize))
    {
        size=query.size();
    }
    else
    {
        query.last();
        size=query.at()+1;
    }

    if(size>0)
    {
        query.seek(size-1);
        return query.value(0).toInt();
    }
    else
        return -1;
}

bool DataBase::addBuilding(const QString &id, int accountId, int streetId, int number, int numberFlat, int peoples, int rateId)
{
    bool hasTransactions=QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions);
    if(hasTransactions)
        QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO number_of_people "
                  "( building, value, active_from )"
                  "VALUES (?, ?, ?);");
    query.addBindValue(id);
    query.addBindValue(peoples);
    query.addBindValue(QDate::currentDate().toString("dd.MM.yyyy"));
    if(!query.exec())
    {
        qDebug()<<"Insert into number_of_people";
        qDebug()<<query.lastError().text();
        if(hasTransactions) QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare("INSERT INTO building "
                  "( id, street, number, number_flat, category ) "
                  "VALUES ( ?, ?, ?, ?, ? )");
    query.addBindValue(id);
    query.addBindValue(streetId);
    query.addBindValue(number);
    query.addBindValue(numberFlat);
    query.addBindValue("POPUL");
    if(!query.exec())
    {
        qDebug()<<"Insert into building";
        qDebug()<<query.lastError().text();
        if(hasTransactions) QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare("INSERT INTO rate_building "
                  "( building, rate, active_from ) "
                  "VALUES ( ?, ?, ? );");
    query.addBindValue(id);
    query.addBindValue(rateId);
    query.addBindValue(QDate::currentDate().toString("dd.MM.yyyy"));
    if(!query.exec())
    {
        qDebug()<<"Insert into rate_building";
        qDebug()<<query.lastError().text();
        if(hasTransactions) QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare("INSERT INTO owner "
                  "(building,  account, active_from )"
                  "VALUES ( ?, ?, ?);");
    query.addBindValue(id);
    query.addBindValue(accountId);
    query.addBindValue(QDate::currentDate().toString("dd.MM.yyyy"));
    if(!query.exec())
    {
        qDebug()<<"Insert into owner";
        qDebug()<<query.lastError().text();
        if(hasTransactions) QSqlDatabase::database().rollback();
        return false;
    }

    return hasTransactions ? QSqlDatabase::database().commit(): true;
}

bool DataBase::infoForAccurals(QSqlQueryModel * model, QString &buildingId)
{
    QSqlQuery query;
    query.prepare("select building.id, street.name, building.number, building.number_flat, number_of_people.value, rate.per_cube "
                  "from building "
                  "inner join street on building.street = street.id "
                  "inner join number_of_people on building.id = number_of_people.building "
                  "inner join rate_building on rate_building.building = building.id "
                  "inner join rate on rate_building.rate = rate.id "
                  "where number_of_people.active_to IS NULL and rate_building.active_to IS NULL and building.id = ? ;");
    query.addBindValue(buildingId);
    query.exec();
    model->setQuery(query);
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return false;
    }
    return true;
}

QList<QString> DataBase::allBuildingId()
{
    QSqlQuery query("select id from building;");
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
        return QList<QString>();
    }
    QList<QString> id;
    while(query.next())
        id.append(query.value(0).toString());
    return id;
}

void DataBase::initPaymentModel(QSqlQueryModel *model)
{
    model->setQuery("select date, ammount from payment limit 0");
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

void DataBase::paymentByAccountId(QSqlQueryModel *model, QString id)
{
    QString query="select "
                  "date, ammount "
                  "from payment "
                  "where building='%1' order by date DESC;";
    model->query().clear();
    model->setQuery(query.arg(id));
}

void DataBase::debt(QSqlQueryModel *model)
{
    QString query="select s.building, sum(s.ammount)/100.0 as ammount "
                    "from "
                    "( select accruals.building, accruals.ammount*(-1) as ammount from accruals "
                    "union all "
                    "select payment.building, payment.ammount from payment ) s "
                    "group by s.building order by s.building;";
    model->query().clear();
    model->setQuery(query);
}

bool DataBase::initRate(QSqlTableModel *model)
{
    model->setTable("rate");
    model->setSort(3, Qt::AscendingOrder);
    model->select();    
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return false;
    }
    return true;
}

int DataBase::getRateIdByBuilding(QString buildingId)
{
    QSqlQuery query;
    query.prepare("select rate from rate_building where active_to IS NULL and building=?;");
    query.addBindValue(buildingId);
    int rateId=-1;
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
    }
    else if(query.next())
    {
        rateId=query.value(0).toInt();
    }
    return rateId;
}

void DataBase::setRateTableHeader(QSqlTableModel *model)
{
    model->setHeaderData(1, Qt::Horizontal, "За м3");
    model->setHeaderData(2, Qt::Horizontal, "м3 на человека");
    model->setHeaderData(3, Qt::Horizontal, "Создан");
}

bool DataBase::allRate(QSqlQueryModel *model)
{
    model->setQuery("select id, per_cube, cube_per_person from rate;");
    if(model->lastError().isValid())
    {
        qDebug()<<model->lastError().text();
        return false;
    }
    return true;
}

bool DataBase::addRate(double value)
{
    QSqlQuery query;
    query.prepare("insert into rate (per_cube, created) values (?, ?);");
    query.addBindValue(value);    
    query.addBindValue(QDate::currentDate().toString("dd.MM.yyyy"));
    return query.exec();
}
