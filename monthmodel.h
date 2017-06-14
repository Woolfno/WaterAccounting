#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QPair>

class MonthModel:public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MonthModel(QObject * parent=0);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

private:
    typedef QPair<int, QString> DatePair;
    QList<DatePair> months;
};

#endif // MONTHMODEL_H
