#include "monthmodel.h"

MonthModel::MonthModel(QObject *parent):QAbstractListModel(parent)
{
    months<<qMakePair(DatePair::first_type(-1), DatePair::second_type("Выберите месяц"))
          <<qMakePair(DatePair::first_type(1), DatePair::second_type("Январь"))
          <<qMakePair(DatePair::first_type(2), DatePair::second_type("Февраль"))
          <<qMakePair(DatePair::first_type(3), DatePair::second_type("Март"))
          <<qMakePair(DatePair::first_type(4), DatePair::second_type("Апрель"))
          <<qMakePair(DatePair::first_type(5), DatePair::second_type("Май"))
          <<qMakePair(DatePair::first_type(6), DatePair::second_type("Июнь"))
          <<qMakePair(DatePair::first_type(7), DatePair::second_type("Июль"))
          <<qMakePair(DatePair::first_type(8), DatePair::second_type("Август"))
          <<qMakePair(DatePair::first_type(9), DatePair::second_type("Сентябрь"))
          <<qMakePair(DatePair::first_type(10),DatePair::second_type("Октябрь"))
          <<qMakePair(DatePair::first_type(11),DatePair::second_type("Ноябрь"))
          <<qMakePair(DatePair::first_type(12),DatePair::second_type("Декабрь"));
}

QVariant MonthModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole || role==Qt::EditRole)
    {
        const DatePair date=months.at(index.row());
        if(index.column()==0)
            return date.first;
        if(index.column()==1)
            return date.second;
    }

    return QVariant();
}

int MonthModel::rowCount(const QModelIndex &parent) const
{
    return months.size();
}

int MonthModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}
