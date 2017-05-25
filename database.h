#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
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

    void allStreet(QSqlQueryModel * model);
    bool addStreet(QString name);

    void initAccrualModel(QSqlQueryModel * model);
    void accrualsSetHeader(QSqlQueryModel *model);
    void accrualsByAccountId(QSqlQueryModel * model, int id);
    bool addAccount(QString &firstName, QString &secondName, QString &lastName);

    void initPaymentModel(QSqlQueryModel * model);
    void paymentSetHeader(QSqlQueryModel * model);
    void paymentByAccountId(QSqlQueryModel * model, int id);

    bool addRate(double value);

private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DATABASE_H
