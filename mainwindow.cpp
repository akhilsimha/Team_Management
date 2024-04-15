#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSql>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{


    QString username = ui->username ->text();
    QString password = ui->password ->text();

    // if(username == "admin" && password == "admin")
    // {
    //     ui->status->setText("Successful");
    // }
    // else
    //     ui->status->setText("Wrong Credential");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // Replace with your hostname
    db.setDatabaseName("company"); // Replace with your database name
    db.setUserName("root"); // Replace with your username
    db.setPassword("password"); // Replace with your password

    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
        return;
    }
    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
        return;
    }

    // Execute a query to fetch the password associated with the username
    QSqlQuery query;
    query.prepare("SELECT password FROM employees WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();

        // Compare the fetched password with the input password
        if (password == storedPassword && username == "admin") {
            ui->status->setText("Successful");
            hide();
            secDialog = new SecDialog (this);
            secDialog -> show();
        }
        else if(password == storedPassword)
        {
            ui->status->setText("Welcome Employee");
            hide();  // Hide the main window
            EHome = new employeeHome(this);  // Create employeeHome instance with parent
            EHome->show();  // Show the employeeHome dialog
        }
        else {
            ui->status->setText("Wrong Credential");
        }
    } else {
        ui->status->setText("User not found");
    }

    db.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}

