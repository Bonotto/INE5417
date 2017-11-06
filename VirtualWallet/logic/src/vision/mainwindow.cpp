#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    facade(new Facade())
{
    ui->setupUi(this);
    ui->Menu->hide();
    ui->MenuWidget->hide();
    ui->MenuButton->setIcon(QIcon(":menubutton.png"));
    ui->MenuButton->setIconSize(QSize(20,20));

    if(!facade->existUser())
        ui->Stack->setCurrentWidget(ui->NewUser);

    ui->NewWallet->setFacade(facade);
    ui->LoginCenterWidget->setFacade(facade);
    ui->ForgotPassCenter->setFacade(facade);
    ui->ForgotNameCenter->setFacade(facade);
    ui->NewUserCenter->setFacade(facade);
    ui->NewBankAccount->setFacade(facade);
    ui->NewReleaseType->setFacade(facade);
    ui->NewRelease->setFacade(facade);
    ui->Home->setFacade(facade);
    ui->Report->setFacade(facade);

    // Connects

    connect(ui->LoginCenterWidget, SIGNAL(configureMenu()), this, SLOT(loginExecuted()));
    connect(ui->LoginCenterWidget, SIGNAL(changeStack(int)), this, SLOT(changeStack(int)));
    connect(ui->LoginCenterWidget, SIGNAL(cleanForgotName()), ui->ForgotNameCenter, SLOT(on_Clean_clicked()));
    connect(ui->LoginCenterWidget, SIGNAL(cleanForgotPassword()), ui->ForgotPassCenter, SLOT(on_Clean_clicked()));

    connect(ui->ForgotPassCenter, SIGNAL(changeStack(int)), this, SLOT(changeStack(int)));
    connect(ui->ForgotPassCenter, SIGNAL(cleanLogin()), ui->LoginCenterWidget, SLOT(on_CleanButton_clicked()));

    connect(ui->ForgotNameCenter, SIGNAL(changeStack(int)), this, SLOT(changeStack(int)));
    connect(ui->ForgotNameCenter, SIGNAL(cleanLogin()), ui->LoginCenterWidget, SLOT(on_CleanButton_clicked()));

    connect(ui->NewUserCenter, SIGNAL(changeStack(int)), this, SLOT(changeStack(int)));
    connect(ui->NewUserCenter, SIGNAL(userRegistred()), ui->LoginCenterWidget, SLOT(changeToNewUserMsg()));

    connect(ui->NewBankAccount, SIGNAL(build()), this, SLOT(build()));
    connect(ui->NewRelease, SIGNAL(build()), this, SLOT(build()));
    connect(ui->NewReleaseType, SIGNAL(build()), this, SLOT(build()));
    connect(ui->NewWallet, SIGNAL(build()), this, SLOT(build()));

    connect(this, SIGNAL(update()), ui->Home, SLOT(tableBuilder()));
    connect(this, SIGNAL(update()), ui->Report, SLOT(tableBuilder()));
    connect(this, SIGNAL(update()), ui->NewWallet, SLOT(tableBuilder()));
    connect(this, SIGNAL(update()), ui->NewBankAccount, SLOT(tableBuilder()));
    connect(this, SIGNAL(update()), ui->NewReleaseType, SLOT(tableBuilder()));
    connect(this, SIGNAL(update()), ui->NewRelease, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MenuButton_clicked()
{
    if (ui->MenuWidget->isHidden()) {
        ui->MenuWidget->show();
    } else {
        ui->MenuWidget->hide();
    }
}

void MainWindow::build()
{
    ui->MenuTotal->setText("Total R$ " + QString::number(facade->accountsBalance(), 'f', 2));
    emit update();
}

void MainWindow::loginExecuted()
{
    ui->MenuUser->setText(QString::fromStdString(facade->getUserName()));
    ui->Stack->setCurrentWidget(ui->Home);
    ui->MenuWidget->hide();
    ui->Menu->show();
    build();
}

void MainWindow::on_MenuNewReleaseType_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewReleaseType);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuNewRelease_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewRelease);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuReport_clicked()
{
    ui->Stack->setCurrentWidget(ui->Report);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuBankAccounts_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewBankAccount);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuWallets_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewWallet);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuAbout_clicked()
{
    ui->Stack->setCurrentWidget(ui->AppAbout);
    ui->MenuWidget->hide();
    build();
}

void MainWindow::on_MenuOut_clicked()
{
    ui->Menu->hide();
    ui->MenuWidget->hide();
    ui->Stack->setCurrentWidget(ui->Login);
}

void MainWindow::changeStack(int _stack)
{
    switch(_stack) {
        case 1: ui->Stack->setCurrentWidget(ui->ForgotPassword); break;
        case 2: ui->Stack->setCurrentWidget(ui->ForgotName); break;
        case 3: ui->Stack->setCurrentWidget(ui->Login); break;
    }
}

void MainWindow::on_MenuHome_clicked()
{
    ui->Stack->setCurrentWidget(ui->Home);
    ui->MenuWidget->hide();
}
