#include "Account.h"

#ifndef BANK_ACCOUNTTYPE_H
#define BANK_ACCOUNTTYPE_H

class Savings : public Account {
public:
    Savings() {}

    explicit Savings(string acc)
    : Account(acc, true) {}

    void withdraw (const float amount, const string reference) {
        if (getStatus()!=0 && getBalance()-amount>=0) {
            Account::withdraw(amount, reference);
        }
        else {
            cout << "Client doesn't have enough funds" << endl;
        }
    }

    void deposit (const float amount, const string reference) {
        if (getStatus()!=0) {
            Account::deposit(amount, reference);
        }
        else if (getStatus()==1 && getBalance()+amount >25) {
            Account::deposit(amount, reference);
        }
        else {
            cout << "Not enough funds to change the status of account to active!" << endl;
        }
    }

    void monthly() {
        if (getnwithdrawal()>4) {                   //monthly service charge for more than 4 withdrawals
            int n = getnwithdrawal() - 4;
            int amount = n * 1;
            setServicecharge(amount);
        }
        Account::monthly();
        changestatus();                         //checking if this results in account going negative
    }
};

class Checking : public Account {
public:
    Checking() {}

    explicit Checking(string acc)
    : Account(acc, true) {}

    void withdraw(const float amount, const string reference) {
        if (getBalance() - amount < 0) {
            if (getBalance() < 0) {
                cout << "Not enough fund for service charge! Please add enough funds to have a minimum balance of $0" << endl;
            } else {
                deductServicecharge(15);
                Account::withdraw(amount, reference);
            }
        }
        else {
            Account::withdraw(amount, reference);
        }
    }

    void monthly() {
        setServicecharge(5 + (0.10 * getnwithdrawal()));
        Account::monthly();
    }
};
#endif //BANK_ACCOUNTTYPE_H
