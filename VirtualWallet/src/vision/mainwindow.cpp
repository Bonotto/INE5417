#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    facade("Nome", "Senha", "Codigo")
{
    ui->setupUi(this);
    ui->Menu->hide();
    ui->MenuWidget->hide();

    if(facade.getUserName() == "")
        ui->Stack->setCurrentWidget(ui->NewUser);

    ui->NewWallet->setFacade(facade);
    ui->LoginCenterWidget->setFacade(facade);
    ui->NewBankAccount->setFacade(facade);
    ui->NewReleaseType->setFacade(facade);
    ui->NewRelease->setFacade(facade);

    // Connects

    connect(ui->NewWallet, SIGNAL(goToHome()), this, SLOT(goToHome()));
    connect(ui->NewBankAccount, SIGNAL(goToHome()), this, SLOT(goToHome()));
    connect(ui->NewReleaseType, SIGNAL(goToHome()), this, SLOT(goToHome()));
    connect(ui->NewRelease, SIGNAL(goToHome()), this, SLOT(goToHome()));

    connect(ui->LoginCenterWidget, SIGNAL(configureMenu()), this, SLOT(configureMenu()));
    connect(ui->LoginCenterWidget, SIGNAL(cleanForgotName()), this, SLOT(on_ForgotNameCleanButton_clicked()));
    connect(ui->LoginCenterWidget, SIGNAL(cleanForgotPassword()), this, SLOT(on_ForgotPassCleanButton_clicked()));
    connect(ui->LoginCenterWidget, SIGNAL(changeStackToForgotName(std::string)), this, SLOT(changeStack(std::string)));
    connect(ui->LoginCenterWidget, SIGNAL(changeStackToForgotPassword(std::string)), this, SLOT(changeStack(std::string)));

    connect(this, SIGNAL(update()), ui->NewRelease, SLOT(update()));

    // Soh para ver se esta add contas
    ui->AccountAmount->setText(QString::number(facade.accountsAmount()));
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

void MainWindow::configureMenu()
{
    std::string accauntsBalance(24, '\0');
    std::snprintf(&accauntsBalance[0], 24, "%.2f", facade.accountsBalance());

    ui->Menu->show();
    ui->MenuButton->setIcon(QIcon("../Images/menubutton.png"));
    ui->MenuUser->setText(QString::fromStdString(facade.getUserName()));
    ui->MenuTotal->setText(QString::fromStdString("Total R$ " + accauntsBalance));
    ui->Stack->setCurrentWidget(ui->Home);

    emit update();
}

void MainWindow::on_MenuNewReleaseType_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewReleaseType);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuNewRelease_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewRelease);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuReport_clicked()
{
    ui->Stack->setCurrentWidget(ui->Report);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuBankAccounts_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewBankAccount);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuWallets_clicked()
{
    ui->Stack->setCurrentWidget(ui->NewWallet);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuUserDatas_clicked()
{
    ui->Stack->setCurrentWidget(ui->UserData);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuAbout_clicked()
{
    ui->Stack->setCurrentWidget(ui->AppAbout);
    ui->MenuWidget->hide();
}

void MainWindow::on_MenuOut_clicked()
{
    ui->Menu->hide();
    ui->MenuWidget->hide();
    ui->Stack->setCurrentWidget(ui->Login);

}

void MainWindow::goToHome()
{
    emit update();
    ui->Stack->setCurrentWidget(ui->Home);
    ui->AccountAmount->setText(QString::number(facade.accountsAmount()));

}

void MainWindow::changeStack(std::string _stack)
{
    if (_stack == "ForgotName")
        ui->Stack->setCurrentWidget(ui->ForgotName);
    if (_stack == "ForgotPassword")
        ui->Stack->setCurrentWidget(ui->ForgotPassword);
}

void MainWindow::on_ForgotPassCleanButton_clicked()
{
    name = false;
    code = false;
    confirm = false;
    password = false;
    ui->ForgotPassName->setText("Nome");
    ui->ForgotPassCode->setText("Codigo");
    ui->ForgotPassNewPass->setText("Nova Senha");
    ui->ForgotPassConfirm->setText("Confirme a Nova Senha");
    ui->ForgotPassName->setStyleSheet("color: #565656; border: none;");
    ui->ForgotPassCode->setStyleSheet("color: #565656; border: none;");
    ui->ForgotPassNewPass->setStyleSheet("color: #565656; border: none;");
    ui->ForgotPassConfirm->setStyleSheet("color: #565656; border: none;");
    ui->ForgotPassErrorMsg->setStyleSheet("color: black; border: none;");
    ui->ForgotPassErrorMsg->setText("Altere sua Senha");
}

void MainWindow::on_ForgotPassName_textEdited(const QString &arg1)
{
    if (!name) {
        QString last(arg1.toStdString().back());
        ui->ForgotPassName->setText(last);
    }
    name = true;
    ui->ForgotPassName->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotPassCode_textEdited(const QString &arg1)
{
    if (!code) {
        QString last(arg1.toStdString().back());
        ui->ForgotPassCode->setText(last);
    }
    code = true;
    ui->ForgotPassCode->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotPassNewPass_textEdited(const QString &arg1)
{
    if (!password) {
        QString last(arg1.toStdString().back());
        ui->ForgotPassNewPass->setText(last);
    }
    password = true;
    ui->ForgotPassNewPass->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotPassConfirm_textEdited(const QString &arg1)
{
    if (!confirm) {
        QString last(arg1.toStdString().back());
        ui->ForgotPassConfirm->setText(last);
    }
    confirm = true;
    ui->ForgotPassConfirm->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotPassBack_clicked()
{
    on_ForgotPassCleanButton_clicked();
    //on_CleanButton_clicked();
    ui->Stack->setCurrentWidget(ui->Login);
}

void MainWindow::on_ForgotPassConfirmButton_clicked()
{
    std::string name = ui->ForgotPassName->text().toStdString();
    std::string code = ui->ForgotPassCode->text().toStdString();
    std::string newpass = ui->ForgotPassNewPass->text().toStdString();
    std::string confirm = ui->ForgotPassConfirm->text().toStdString();
    if (facade.verifyNewPass(name, code, newpass, confirm)) {
        facade.refreshPass(newpass);
        on_ForgotPassCleanButton_clicked();
        ui->ForgotPassErrorMsg->setStyleSheet("color: #00c10d; border: none;");
        ui->ForgotPassErrorMsg->setText("Alteraçao Realizada com Sucesso!");
    } else {
        on_ForgotPassCleanButton_clicked();
        ui->ForgotPassErrorMsg->setStyleSheet("color: rgb(250, 0, 0); border: none;");
        ui->ForgotPassErrorMsg->setText("Dados Invalidos!");
    }
}

void MainWindow::on_ForgotNameCode_textEdited(const QString &arg1)
{
    if (!code) {
        QString last(arg1.toStdString().back());
        ui->ForgotNameCode->setText(last);
    }
    code = true;
    ui->ForgotNameCode->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotNamePassword_textEdited(const QString &arg1)
{
    if (!password) {
        QString last(arg1.toStdString().back());
        ui->ForgotNamePassword->setText(last);
    }
    password = true;
    ui->ForgotNamePassword->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotNameNewName_textEdited(const QString &arg1)
{
    if (!name) {
        QString last(arg1.toStdString().back());
        ui->ForgotNameNewName->setText(last);
    }
    name = true;
    ui->ForgotNameNewName->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotNameConfirm_textEdited(const QString &arg1)
{
    if (!confirm) {
        QString last(arg1.toStdString().back());
        ui->ForgotNameConfirm->setText(last);
    }
    confirm = true;
    ui->ForgotNameConfirm->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_ForgotNameCleanButton_clicked()
{
    name = false;
    code = false;
    confirm = false;
    password = false;
    ui->ForgotNameCode->setText("Codigo");
    ui->ForgotNamePassword->setText("Senha");
    ui->ForgotNameNewName->setText("Novo Nome");
    ui->ForgotNameConfirm->setText("Confirme o Novo Nome");
    ui->ForgotNameCode->setStyleSheet("color: #565656; border: none;");
    ui->ForgotNamePassword->setStyleSheet("color: #565656; border: none;");
    ui->ForgotNameNewName->setStyleSheet("color: #565656; border: none;");
    ui->ForgotNameConfirm->setStyleSheet("color: #565656; border: none;");
    ui->ForgotNameErrorMsg->setStyleSheet("color: black; border: none;");
    ui->ForgotNameErrorMsg->setText("Altere seu Nome");
}

void MainWindow::on_ForgotNameBack_clicked()
{
    on_ForgotNameCleanButton_clicked();
    //on_CleanButton_clicked();
    ui->Stack->setCurrentWidget(ui->Login);
}

void MainWindow::on_ForgotNameConfirmButton_clicked()
{
    std::string code = ui->ForgotNameCode->text().toStdString();
    std::string password = ui->ForgotNamePassword->text().toStdString();
    std::string newName = ui->ForgotNameNewName->text().toStdString();
    std::string confirm = ui->ForgotNameConfirm->text().toStdString();
    if (facade.verifyNewName(code, password, newName, confirm)) {
        facade.refreshName(newName);
        on_ForgotNameCleanButton_clicked();
        ui->ForgotNameErrorMsg->setStyleSheet("color: #00c10d; border: none;");
        ui->ForgotNameErrorMsg->setText("Alteraçao Realizada com Sucesso!");
    } else {
        on_ForgotNameCleanButton_clicked();
        ui->ForgotNameErrorMsg->setStyleSheet("color: rgb(250, 0, 0); border: none;");
        ui->ForgotNameErrorMsg->setText("Dados Invalidos!");
    }
}

void MainWindow::on_NewUserName_textEdited(const QString &arg1)
{
    if (!name) {
        QString last(arg1.toStdString().back());
        ui->NewUserName->setText(last);
    }
    name = true;
    ui->NewUserName->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_NewUserCode_textEdited(const QString &arg1)
{
    if (!code) {
        QString last(arg1.toStdString().back());
        ui->NewUserCode->setText(last);
    }
    code = true;
    ui->NewUserCode->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_NewUserPassword_textEdited(const QString &arg1)
{
    if (!password) {
        QString last(arg1.toStdString().back());
        ui->NewUserPassword->setText(last);
    }
    password = true;
    ui->NewUserPassword->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_NewUserConfirm_textEdited(const QString &arg1)
{
    if (!confirm) {
        QString last(arg1.toStdString().back());
        ui->NewUserConfirm->setText(last);
    }
    confirm = true;
    ui->NewUserConfirm->setStyleSheet("color: rgb(0, 0, 0); border: none;");
}

void MainWindow::on_NewUserCleanButton_clicked()
{
    name = false;
    code = false;
    confirm = false;
    password = false;
    ui->NewUserName->setText("Nome");
    ui->NewUserCode->setText("Codigo");
    ui->NewUserPassword->setText("Senha");
    ui->NewUserConfirm->setText("Confirme a Senha");
    ui->NewUserName->setStyleSheet("color: #565656; border: none;");
    ui->NewUserCode->setStyleSheet("color: #565656; border: none;");
    ui->NewUserPassword->setStyleSheet("color: #565656; border: none;");
    ui->NewUserConfirm->setStyleSheet("color: #565656; border: none;");
    ui->NewUserMsg->setStyleSheet("color: black; border: none;");
    ui->NewUserMsg->setText("Crie seu Usuario");
}

void MainWindow::on_NewUserConfirmButton_clicked()
{
    std::string name = ui->NewUserName->text().toStdString();
    std::string code = ui->NewUserCode->text().toStdString();
    std::string password = ui->NewUserPassword->text().toStdString();
    std::string confirm = ui->NewUserConfirm->text().toStdString();
    if (facade.registerUser(name, code, password, confirm)) {
        on_NewUserCleanButton_clicked();
        //on_CleanButton_clicked();
        //ui->LoginMsg->setStyleSheet("color: #00c10d; border: none;");
        //ui->LoginMsg->setText("Usuario Criado com Sucesso!");
        ui->Stack->setCurrentWidget(ui->Login);
    } else {
        on_NewUserCleanButton_clicked();
        ui->NewUserMsg->setStyleSheet("color: rgb(250, 0, 0); border: none;");
        ui->NewUserMsg->setText("Dados Invalidos!");
    }   
}
