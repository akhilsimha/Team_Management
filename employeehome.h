#ifndef EMPLOYEEHOME_H
#define EMPLOYEEHOME_H

#include <QDialog>

namespace Ui {
class employeeHome;
}

class employeeHome : public QDialog
{
    Q_OBJECT

public:
    explicit employeeHome(QWidget *parent = nullptr);
    ~employeeHome();

private slots:
    void on_pushButton_clicked();

    void on_updateButton_clicked();

    void on_projects_activated(int index);

    void on_tableView_viewportEntered();

private:
    Ui::employeeHome *ui;
};

#endif // EMPLOYEEHOME_H
