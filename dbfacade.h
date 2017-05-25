#ifndef DBFACADE_H
#define DBFACADE_H
#include <QObject>
#include <QTableView>
#include <QListView>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class DBFacade:public QObject
{
    Q_OBJECT
public:
    DBFacade(QTableView * mainView, QListView * streetView, QObject * parent=0);

protected:
    void exec(QString );
    QSqlDatabase m_db;
    QSqlQuery * m_query;
    QSqlRecord m_rec;
    QSqlTableModel * m_mainModel;
    QSqlQueryModel * m_streetModel;
};

#endif // DBFACADE_H
