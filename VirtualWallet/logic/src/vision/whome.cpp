#include "whome.h"
#include "ui_whome.h"

#include <iostream>

WHome::WHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WHome)
{
    ui->setupUi(this);

    QStringList titles;
    titles << "Conta" << "Montante (R$)";

    ui->Table->setColumnCount(2);
    ui->Table->setColumnWidth(0, 224);
    ui->Table->setColumnWidth(1, 224);
    ui->Table->setHorizontalHeaderLabels(titles);
    ui->Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void WHome::setFacade(Facade * _facade)
{
    facade = _facade;
}

WHome::~WHome()
{
    delete ui;
}

void WHome::tableBuilder()
{
    ui->Table->setRowCount(0);
    for (auto i : facade->userAccounts()) {
        ui->Table->insertRow(ui->Table->rowCount());
        ui->Table->setItem(ui->Table->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(i->getName())));
        ui->Table->setItem(ui->Table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(i->getBalance())));
    }
}
