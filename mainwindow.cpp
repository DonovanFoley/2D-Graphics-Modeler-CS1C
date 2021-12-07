#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

// for testing rn
void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username == "user" && password == "pass")
    {
        QMessageBox::information(this, "Login", "Username and password are correct.");
        hide(); // hides login window upon successful login
        SecDialog = new secDialog(this);
        SecDialog->show();
    }
    else if (username == "admin" && password == "pass")
    {
        QMessageBox::information(this, "Login", "Admin login enabled.");
        adminLog = true;    // will be used later in order to enable admin privileges
        hide();
        SecDialog = new secDialog(this);
        SecDialog->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Incorrect username and password!");
    }
}

