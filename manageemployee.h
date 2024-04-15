#ifndef MANAGEEMPLOYEE_H
#define MANAGEEMPLOYEE_H

#include <QDialog>

namespace Ui {
class manageEmployee;
}

class manageEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit manageEmployee(QWidget *parent = nullptr);
    ~manageEmployee();

private slots:
    void on_exit_clicked();

    void on_addEmployee_clicked();

    void displayEmployees();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::manageEmployee *ui;
};

#endif // MANAGEEMPLOYEE_H
