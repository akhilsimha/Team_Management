#include "adminHome.h"
#include "ui_adminHome.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QtSql/QSqlError>

SecDialog::SecDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    on_tableView();
    on_projectHoursTable();
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    // Close the current dialog
    close();

    // Show the main window again
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void SecDialog::on_manageEmployee_clicked()
{
    hide();
    mEmployee = new manageEmployee(this);
    mEmployee -> show();

}


void SecDialog::on_tableView()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // Adjust for your database
    db.setHostName("localhost");
    db.setDatabaseName("company");
    db.setUserName("root");
    db.setPassword("password"); // Consider secure storage
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError();
        return;
    }

    // Employee work hours per project
    QStandardItemModel *employeeHoursModel = new QStandardItemModel(0, 3, this);
    employeeHoursModel->setHeaderData(0, Qt::Horizontal, "Employee Name");
    employeeHoursModel->setHeaderData(1, Qt::Horizontal, "Project Name");
    employeeHoursModel->setHeaderData(2, Qt::Horizontal, "Total Hours");

    QSqlQuery employeeHoursQuery(db);
    employeeHoursQuery.prepare("SELECT e.name AS employee_name, p.name AS project_name, SUM(wh.hours_worked) AS total_hours "
                               "FROM employees e "
                               "JOIN workhours wh ON e.employee_id = wh.employee_id "
                               "JOIN projects p ON wh.project_id = p.project_id "
                               "GROUP BY e.name, p.name "
                               "ORDER BY e.name, p.name;");

    if (!employeeHoursQuery.exec()) {
        qDebug() << "Error executing employee hours query: " << employeeHoursQuery.lastError();
    } else {
        while (employeeHoursQuery.next()) {
            QString employeeName = employeeHoursQuery.value(0).toString();
            QString projectName = employeeHoursQuery.value(1).toString();
            double totalHours = employeeHoursQuery.value(2).toDouble();

            QList<QStandardItem*> row;
            row.append(new QStandardItem(employeeName));
            row.append(new QStandardItem(projectName));
            row.append(new QStandardItem(QString::number(totalHours)));
            employeeHoursModel->appendRow(row);
        }
    }

    ui->employeeHoursTable->setModel(employeeHoursModel);
    // Total project hours
    QStandardItemModel *totalProjectHoursModel = new QStandardItemModel(0, 2, this);
    totalProjectHoursModel->setHeaderData(0, Qt::Horizontal, "Project Name");
    totalProjectHoursModel->setHeaderData(1, Qt::Horizontal, "Total Hours");

    QSqlQuery totalProjectHoursQuery(db);
    totalProjectHoursQuery.prepare("SELECT p.name AS project_name, SUM(wh.hours_worked) AS total_hours "
                                   "FROM workhours wh "
                                   "JOIN projects p ON wh.project_id = p.project_id "
                                   "GROUP BY p.name "
                                   "ORDER BY p.name;");

    if (!totalProjectHoursQuery.exec()) {
        qDebug() << "Error executing total project hours query: " << totalProjectHoursQuery.lastError();
    } else {
        while (totalProjectHoursQuery.next()) {
            QString projectName = totalProjectHoursQuery.value(0).toString();
            double totalHours = totalProjectHoursQuery.value(1).toDouble();

            QList<QStandardItem*> row;
            row.append(new QStandardItem(projectName));
            row.append(new QStandardItem(QString::number(totalHours)));
            totalProjectHoursModel->appendRow(row);
        }
}
}

void SecDialog::on_projectHoursTable()
{

    // Connect to database (replace with your connection logic)
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // Adjust for your database
    db.setHostName("localhost");
    db.setDatabaseName("company");
    db.setUserName("root");
    db.setPassword("password"); // Consider secure storage
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError();
        return;
    }

    // Total project hours
    QStandardItemModel *totalProjectHoursModel = new QStandardItemModel(0, 2, this);
    totalProjectHoursModel->setHeaderData(0, Qt::Horizontal, "Project Name");
    totalProjectHoursModel->setHeaderData(1, Qt::Horizontal, "Total Hours");

    QSqlQuery totalProjectHoursQuery(db);
    totalProjectHoursQuery.prepare("SELECT p.name AS project_name, SUM(wh.hours_worked) AS total_hours "
                                   "FROM workhours wh "
                                   "JOIN projects p ON wh.project_id = p.project_id "
                                   "GROUP BY p.name "
                                   "ORDER BY p.name;");

    if (!totalProjectHoursQuery.exec()) {
        qDebug() << "Error executing total project hours query: " << totalProjectHoursQuery.lastError();
    } else {
        while (totalProjectHoursQuery.next()) {
            QString projectName = totalProjectHoursQuery.value(0).toString();
            double totalHours = totalProjectHoursQuery.value(1).toDouble();

            QList<QStandardItem*> row;
            row.append(new QStandardItem(projectName));
            row.append(new QStandardItem(QString::number(totalHours)));
            totalProjectHoursModel->appendRow(row);
        }
    }

    ui->projectHoursTable->setModel(totalProjectHoursModel);

    db.close();  // Close the database connection
}
