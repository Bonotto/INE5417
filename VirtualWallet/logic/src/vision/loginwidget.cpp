#include "loginwidget.h"
#include "ui_loginwidget.h"

#include <iostream>

loginwidget::loginwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwidget)
{
    ui->setupUi(this);
    ui->LoginName->setPlaceholderText("Nome");
    ui->LoginPassword->setPlaceholderText("Senha");
    ui->LoginPassword->setEchoMode(QLineEdit::Password);
}

loginwidget::~loginwidget()
{
    delete ui;
}

void loginwidget::setFacade(Facade * _facade) {
    facade = _facade;
}

void loginwidget::on_CleanButton_clicked()
{
    ui->LoginPassword->setText("");
    ui->LoginName->setText("");
    ui->LoginMsg->setText("");
}

void loginwidget::on_ConfirmButton_clicked()
{
    std::string name = ui->LoginName->text().toStdString();
    std::string password = ui->LoginPassword->text().toStdString();
    on_CleanButton_clicked();
    if (facade->login(name, password)) {
        emit configureMenu();
    } else {
        ui->LoginMsg->setStyleSheet("color: rgb(250, 0, 0); border: none;");
        ui->LoginMsg->setText("Usuario ou Senha Invalidos!");
    }
}

void loginwidget::on_LoginPasswordForgot_clicked()
{
    emit cleanForgotPassword();
    emit changeStack(1);
}

void loginwidget::on_LoginNameForgot_clicked()
{
    emit cleanForgotName();
    emit changeStack(2);
}

void loginwidget::changeToNewUserMsg()
{
    on_CleanButton_clicked();
    ui->LoginMsg->setStyleSheet("color: #00c10d; border: none;");
    ui->LoginMsg->setText("Usuario Criado com Sucesso!");
    ui->LoginName->setFocus();
}
