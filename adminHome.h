#ifndef ADMINHOME_H
#define ADMINHOME_H

#include <QDialog>
#include "manageemployee.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

    void on_manageEmployee_clicked();

    void on_tableView();

    void on_projectHoursTable();

private:
    Ui::SecDialog *ui;
    manageEmployee *mEmployee;
};

#endif // ADMINHOME_H
