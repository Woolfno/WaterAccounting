#ifndef STREETDIALOG_H
#define STREETDIALOG_H
#include <QDialog>
#include <QCloseEvent>
#include "ui_addstreetdialog.h"

class StreetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StreetDialog(QWidget * parent=0);    
    ~StreetDialog();

    QString getStreetName() const;
    void setStreetName(const QString &value);

private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddStreetDialog ui;
    QString streetName;
};

#endif // STREETDIALOG_H
