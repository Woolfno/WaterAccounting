#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QAbstractItemModel>

class Category
{
private:
    int id;
    QString name;

public:
    Category(int id, QString n);
    ~Category(){}
};

class CategoryModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CategoryModel(QObject *parent=0);
    ~CategoryModel();
};

#endif // CATEGORYMODEL_H
