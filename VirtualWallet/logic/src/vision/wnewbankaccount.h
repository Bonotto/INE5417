#ifndef WNEWBANKACCOUNT_H
#define WNEWBANKACCOUNT_H

#include <QWidget>
#include "./src/control/Facade.h"

using namespace project;

namespace Ui {
class WNewBankAccount;
}

class WNewBankAccount : public QWidget
{
    Q_OBJECT

public:
    explicit WNewBankAccount(QWidget *parent = 0);
    ~WNewBankAccount();

    void setFacade(Facade &_facade);

public slots:
    void tableBuilder();

private slots:
    void on_Clean_clicked();

    void on_Confirm_clicked();

    void on_Delete_clicked();

    void on_AccountTable_clicked(const QModelIndex &index);

signals:
    void build();

private:
    Ui::WNewBankAccount *ui;
    Facade * facade;
};

#endif // WNEWBANKACCOUNT_H
