#include "datedelegate.h"

void DateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
  QString text = index.model()->data(index, Qt::DisplayRole).toString();
  QStyleOptionViewItem myOption = option;
  myOption.displayAlignment = Qt::AlignCenter | Qt::AlignVCenter;
  drawDisplay(painter, myOption, myOption.rect, text);
  drawFocus(painter, myOption, myOption.rect);
}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
  QDateEdit *dateEdit = new QDateEdit(parent);
  dateEdit->setDisplayFormat("dd.MM.yyyy");
  dateEdit->setCalendarPopup(true);
  return dateEdit;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QDate date = index.model()->data(index, Qt::DisplayRole).toDate();
  if (date == QDate()) date = QDate::currentDate();
  QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
  dateEdit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
  QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
  QDate date = dateEdit->date();
  model->setData(index, date.toString("dd.MM.yyyy"));
}
