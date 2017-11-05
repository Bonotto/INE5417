#include "wnewrelease.h"
#include "ui_wnewrelease.h"

#include <iostream>

WNewRelease::WNewRelease(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WNewRelease)
{
    ui->setupUi(this);
    ui->DescRelease->setPlaceholderText("Descricao");
    ui->DateEdit->setDisplayFormat("dd/MM/yyyy");

    QStringList titles;
    titles << "Id" << "Conta/Cart." << "Tp. Lcto." << "Tp. Pgto." << "Op." << "Data" << "Valor (R$)";

    ui->ReleaseTable->setColumnCount(7);
    ui->ReleaseTable->setColumnWidth(0, 25);
    ui->ReleaseTable->setColumnWidth(1, 85);
    ui->ReleaseTable->setColumnWidth(2, 85);
    ui->ReleaseTable->setColumnWidth(3, 65);
    ui->ReleaseTable->setColumnWidth(4, 25);
    ui->ReleaseTable->setColumnWidth(5, 80);
    ui->ReleaseTable->setColumnWidth(6, 70);
    ui->ReleaseTable->setHorizontalHeaderLabels(titles);
    ui->ReleaseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

WNewRelease::~WNewRelease()
{
    delete ui;
}

void WNewRelease::setFacade(Facade * _facade) {
    facade = _facade;
}

void WNewRelease::update() {

    on_Clean_clicked();
    ui->Accounts->clear();
    ui->ReleaseType->clear();
    ui->PaymentType->clear();

    ui->Accounts->addItem("Conta");
    ui->ReleaseType->addItem("Tipo de Lancamento");
    ui->PaymentType->addItem("Tipo de Pagamento");
    ui->DateEdit->setDate(QDate::currentDate());

    for (auto acc : facade->userAccounts()) {
        ui->Accounts->addItem(QString::fromStdString(acc->getName()));
    }

    for (auto release : facade->userReleaseTypes()) {
        ui->ReleaseType->addItem(QString::fromStdString(release->getName()));
    }

    for (auto payT : facade->userPaymentTypes()) {
        ui->PaymentType->addItem(QString::fromStdString(payT));
    }
    tableBuilder();
}

void WNewRelease::on_Clean_clicked()
{
    ui->ValueBox->setValue(0.0);
    ui->Accounts->setCurrentIndex(0);
    ui->ReleaseType->setCurrentIndex(0);
    ui->PaymentType->setCurrentIndex(0);
    ui->DateEdit->setDate(QDate::currentDate());
    ui->DescRelease->setText("");
    ui->Msg->setText("");
    ui->In->setAutoExclusive(false);
    ui->In->setChecked(false);
    ui->Out->setChecked(false);
    ui->In->setAutoExclusive(true);
    ui->ReleaseTable->setCurrentCell(-1,-1);
    ui->ReleaseTable->clearSelection();
}

void WNewRelease::on_Confirm_clicked()
{
    std::string account = ui->Accounts->currentText().toStdString();
    std::string releaseType = ui->ReleaseType->currentText().toStdString();
    std::string paymenteType = ui->PaymentType->currentText().toStdString();
    std::string description = ui->DescRelease->toPlainText().toStdString();
    std::string operation = ui->In->isChecked()? "in" : ui->Out->isChecked()? "out" : "error";
    std::string date = ui->DateEdit->date().toString("dd/MM/yyyy").toStdString();
    double value = ui->ValueBox->value();

    int row = ui->ReleaseTable->currentRow();

    if (row > -1)
        row = ui->ReleaseTable->item(row, 0)->text().toInt();

    on_Clean_clicked();

    if (facade->registerRelease(row, value, account, releaseType, paymenteType, description, operation, date)) {
        ui->Msg->setStyleSheet("color: green");
        ui->Msg->setText("Operaçao Realizada com Sucesso!");
        emit build();
    } else {
        ui->Msg->setStyleSheet("color: red");
        ui->Msg->setText("Dados Invalidos!");
    }

    tableBuilder();
}

void WNewRelease::tableBuilder()
{
    ui->ReleaseTable->setRowCount(0);
    for (auto & rel : facade->userReleases()) {
        ui->ReleaseTable->insertRow(ui->ReleaseTable->rowCount());
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(rel->getId())));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(rel->getAccount()->getName())));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(rel->getReleaseType()->getName())));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(rel->getPaymentType())));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 4, new QTableWidgetItem(QString::fromStdString(rel->getOperation().compare("out") ? "E" : "S")));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 5, new QTableWidgetItem(QString::fromStdString(rel->getDate())));
        ui->ReleaseTable->setItem(ui->ReleaseTable->rowCount() - 1, 6, new QTableWidgetItem(QString::number(rel->getValue())));
    }
}

void WNewRelease::on_ReleaseTable_clicked(const QModelIndex &index)
{
    int id = ui->ReleaseTable->item(index.row(), 0)->text().toInt();
    Release * release;
    for (auto & rel : facade->userReleases())
        if (rel->getId() == id) {
            release = rel;
            break;
        }

    ui->ValueBox->setValue(release->getValue());
    ui->DateEdit->setDate(QDate::fromString(QString::fromStdString(release->getDate()), "dd/MM/yyyy"));
    ui->DescRelease->setText(QString::fromStdString(release->getDescription()));

    if (release->getOperation() == "in")
        ui->In->setChecked(true);
    else
        ui->Out->setChecked(true);

    ui->Accounts->setCurrentText(QString::fromStdString(release->getAccount()->getName()));
    ui->ReleaseType->setCurrentText(QString::fromStdString(release->getReleaseType()->getName()));
    ui->PaymentType->setCurrentText(QString::fromStdString(release->getPaymentType()));
}

void WNewRelease::on_Delete_clicked()
{
    int row = ui->ReleaseTable->currentRow();

    if (row < 0) {
        ui->Msg->setStyleSheet("color: red");
        ui->Msg->setText("Nenhum Lancamento Selecionado!");
    } else {
        facade->deleteRelease(ui->ReleaseTable->item(row, 0)->text().toInt());
        ui->Msg->setStyleSheet("color: green");
        ui->Msg->setText("Lancamento Excluido com Sucesso!");
        tableBuilder();
        emit build();
    }
}
