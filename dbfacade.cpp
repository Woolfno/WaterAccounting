#include "dbfacade.h"
#include <QDebug>

DBFacade::DBFacade(QTableView * mainView, QListView *streetView, QObject * parent):
    QObject(parent)
{
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("water.db");

    if(!m_db.open())
        throw "can`t open database";

    m_query=new QSqlQuery(m_db);
    if(!m_db.tables().contains("account"))
        qDebug()<<"Error";

    m_mainModel=new QSqlTableModel(this, m_db);
    m_streetModel=new QSqlQueryModel(this);
    m_streetModel->setQuery("SELECT name FROM street");
    streetView->setModel(m_streetModel);
}
