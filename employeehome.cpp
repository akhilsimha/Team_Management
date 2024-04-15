#include "employeehome.h"
#include "ui_employeehome.h"
#include "mainwindow.h"
#include <QtSql>

employeeHome::employeeHome(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::employeeHome)
{
    ui->setupUi(this);
    on_projects_activated(1);


}

employeeHome::~employeeHome()
{
    delete ui;
}

void employeeHome::on_pushButton_clicked()
{
    // Close the current dialog
    close();

    // Show the main window again
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void employeeHome::on_updateButton_clicked() {

    // Get selected project ID
    QComboBox *projectsComboBox = ui->projects;  // Assuming you have a pointer to the QComboBox
    int selectedProjectIndex = projectsComboBox->currentIndex();

    // Check if a project is selected
    if (selectedProjectIndex == -1) {
        qDebug() << "Please select a project from the dropdown";
        return;  // Exit if no project selected
    }

    // Assuming you have a way to get the employee ID (e.g., from login information)
    int employeeID = 2;

    QString projectWorkHours = ui->hours->text();
    QString projectWorkMinutes = ui->Minutes->text();

    // Convert hours and minutes to a single decimal value (adjust based on your data format)
    double totalHours = projectWorkHours.toDouble() + projectWorkMinutes.toDouble() / 60.0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  // Adjust for your database
    db.setHostName("localhost");
    db.setDatabaseName("company");
    db.setUserName("root");
    db.setPassword("password");
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError();
        return;
    }

    QSqlQuery query(db);

    // Assuming you have a way to get the project ID based on the selected index
    int selectedProjectID = 1;

    query.prepare("INSERT INTO workhours (employee_id, project_id, work_date, hours_worked) "
                  "VALUES (:employeeID, :projectID, CURDATE(), :hoursWorked)");
    query.bindValue(":employeeID", employeeID);
    query.bindValue(":projectID", selectedProjectID);
    query.bindValue(":hoursWorked", totalHours);

    if (!query.exec()) {
        qDebug() << "Error inserting work hours: " << query.lastError();
    } else {
        qDebug() << "Work hours recorded successfully!";
        // ... (clear input fields or provide feedback to the user)
    }

    db.close();  // Close the database connection
    // ... (rest of your code)
    ui->successMessage->setText("Work hours recorded successfully!");

    // Clear the message after a short delay (optional)
    QTimer::singleShot(2000, ui->successMessage, SLOT(clear()));
}




void employeeHome::on_projects_activated(int index)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  // Adjust for your database
    db.setHostName("localhost");
    db.setDatabaseName("company");
    db.setUserName("root");
    db.setPassword("password");
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError();
        return;
    }

    QComboBox *projectsComboBox = ui->projects; // Assuming you have a pointer to the QComboBox

    QSqlQuery query(db);
    query.prepare("SELECT name FROM projects");
    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError();
        return;
    }

    while (query.next()) {
        QString projectName = query.value(0).toString();
        projectsComboBox->addItem(projectName);
    }

    db.close();


}



void employeeHome::on_tableView_viewportEntered()
{

}

