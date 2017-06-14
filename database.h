#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

#define DATABASE_NAME  "water.db"
#define ACCOUNT_TABLE  "account"
#define BUILDING_TABLE "building"
#define STREET_TABLE   "street"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    bool connect();

    void accountSetHeader(QSqlQueryModel * model);
    void accountByStreetId(QSqlQueryModel * model, int id);    

    void organizationByStreetId(QSqlQueryModel *model, int id);

    void allStreet(QSqlQueryModel * model);
    bool addStreet(QString name);
    bool deleteStreet(int streetId);
    bool updateStreet(int streetId, QString streetName);

    void initAccrualModel(QSqlQueryModel * model);
    void accrualsSetHeader(QSqlQueryModel *model);
    void accrualsByBuildingId(QSqlQueryModel * model, QString &id);
    bool addAccural(QString buildingId, int rateId, int64_t ammount, int month);

    int  addAccount(QString &firstName, QString &secondName, QString &lastName);
    bool accountById(QSqlQueryModel * model, int id);
    bool updateAccount(int accountId, const QString &fname, const QString &sname, const QString &lname);
    bool addAccountWithHouse(QString &firstName, QString &secondName, QString &lastName, int streetId, int numberHouse);
    bool allAccounts(QSqlQueryModel * model, bool concatName=false);
    void accountByListId(QSqlQueryModel * model, QList<int> &listId);
    void accountByListIdName(QSqlQueryModel * model, QList<int> &list);
    QList<int> accountSearch(const QString &pattern);

    bool changeBuildingOwen(int ownerId, int buildingId);
    int  getBuildingId(int streetId, int numberHouse, int numberFlat, bool hasOwner=true);
    bool addBuilding(const QString &id, int accountId, int streetId, int number, int numberFlat, int peoples, int rateId);
    bool infoForAccurals(QSqlQueryModel *model, QString &buildingId);
    QList<QString> allBuildingId();

    void initPaymentModel(QSqlQueryModel * model);
    void paymentSetHeader(QSqlQueryModel * model);
    void paymentByAccountId(QSqlQueryModel * model, QString id);

    void debt(QSqlQueryModel * model);

    bool initRate(QSqlTableModel * model);
    int  getRateIdByBuilding(QString buildingId);
    void setRateTableHeader(QSqlTableModel * model);
    bool allRate(QSqlQueryModel *model);    
    bool addRate(double value);

private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DATABASE_H
