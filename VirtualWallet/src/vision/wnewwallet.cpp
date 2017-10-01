#include "wnewwallet.h"
#include "ui_wnewwallet.h"
#include <iostream>

WNewWallet::WNewWallet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WNewWallet)
{
    ui->setupUi(this);
    ui->Name->setPlaceholderText("Nome");
}

WNewWallet::~WNewWallet()
{
    delete ui;
}

void WNewWallet::setFacade(Facade &_facade)
{
    facade = &_facade;
}

void WNewWallet::on_Clean_clicked()
{
    ui->Name->setText("");
    ui->Name->setStyleSheet("color: #565656; border: none;");
    ui->Balance->setValue(0.0);
    ui->Balance->setStyleSheet("color: #565656; border: none;");
    ui->Erro->setText("");
}

void WNewWallet::on_Confirm_clicked()
{
    std::string finalName = ui->Name->text().toStdString();
    double _balance = ui->Balance->value();

    if (finalName != "") {
        if (facade->registerWallet(finalName, _balance)) {
            on_Clean_clicked();
            emit goToHome();
        } else {
            ui->Erro->setText("Nome invalido!");
        }
    } else {
        ui->Erro->setText("Nome invalido!");
    }
}
