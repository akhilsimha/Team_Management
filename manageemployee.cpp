#include "manageemployee.h"
#include "ui_manageemployee.h"
#include <QtSql>
#include "mainwindow.h"
manageEmployee::manageEmployee(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::manageEmployee)
{
    ui->setupUi(this);
    displayEmployees();
}

manageEmployee::~manageEmployee()
{
    delete ui;
}

void manageEmployee::on_exit_clicked()
{
    close();
}


void manageEmployee::on_addEmployee_clicked()
{
    QString name = ui->name->text();
    QString EmpUsername = ui->username->text();
    QString EmpPassword = ui->password->text();

    // Connect to your SQL database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // Replace with your hostname
    db.setDatabaseName("company"); // Replace with your database name
    db.setUserName("root"); // Replace with your username
    db.setPassword("password"); // Replace with your password

    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
        return;
    }

    // Execute an SQL INSERT statement to add the data to the employees table
    QSqlQuery query;
    query.prepare("INSERT INTO employees (name, username, password) VALUES (:name, :username, :password)");
    query.bindValue(":name", name);
    query.bindValue(":username", EmpUsername);
    query.bindValue(":password", EmpPassword);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    qDebug() << "Employee added successfully";

    db.close();
}

void manageEmployee::displayEmployees()
{

    // Connect to your SQL database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // Replace with your hostname
    db.setDatabaseName("company"); // Replace with your database name
    db.setUserName("root"); // Replace with your username
    db.setPassword("password"); // Replace with your password

    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
        return;
    }

    // Execute an SQL SELECT statement to fetch data from the employees table
    QSqlQuery query("SELECT name, username FROM employees");

    // Set up the table widget with appropriate headers
    ui->tableWidget->setColumnCount(2); // Three columns: name, username, password
    ui->tableWidget->setHorizontalHeaderLabels({"Name", "Username"});

    int row = 0;
    // Populate the table widget with data from the query result
    while (query.next()) {
        QString name = query.value(0).toString();
        QString username = query.value(1).toString();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(username));

        row++;
    }

    db.close();
}

void manageEmployee::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0); // Reset the row count to 0

    // Refresh the QTableWidget
    displayEmployees();

}


void manageEmployee::on_pushButton_2_clicked()
{
        // Close the current dialog
        close();

        // Show the main window again
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
}

