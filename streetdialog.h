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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddStreetDialog ui;
    QString streetName;
    bool valid;
};

#endif // STREETDIALOG_H
