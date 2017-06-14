#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>
#include <QDateEdit>
#include <QDate>

class DateDelegate : public QItemDelegate
{
  Q_OBJECT

public:
  DateDelegate(QObject *parent=0)
    : QItemDelegate(parent) {}

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};

#endif // DATEDELEGATE_H
