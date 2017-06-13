#ifndef TABLERATEDIALOG_H
#define TABLERATEDIALOG_H

#include <QDialog>

namespace Ui {
class TableRateDialog;
}

class TableRateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableRateDialog(QWidget *parent = 0);
    ~TableRateDialog();

private:
    Ui::TableRateDialog *ui;
};

#endif // TABLERATEDIALOG_H
