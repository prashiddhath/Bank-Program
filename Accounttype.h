#ifndef BANK_ACCOUNTTYPE_H
#define BANK_ACCOUNTTYPE_H

#include "Account.h"

class Savings : public Account {
public:
    Savings() {}

    explicit Savings(string acc)
    : Account(acc, true) {}

    /**
    * Withdraws Money from Client's Savings Account
    * 
    * The client can only withdraw if the bank account is active and has enough funds for the withdrawal
    *
    * @param {float} amount - Amount to withdraw from client's bank account
    * @return none
    */
    void withdraw (const float amount, const string& reference) {
        if (getStatus()!=0 && getBalance()-amount>=0) {
            Account::withdraw(amount, reference);
        }
        else {
            cout << "Client doesn't have enough funds" << endl;
        }
    }

    /**
    * Deposits Money to Client's Savings Account
    * 
    * The client can deposit:
    *          1) If their bank account is active
    *          2) If their bank account is inactive but the balance, after depositing, is more than $25
    *
    * @param {float} amount - Amount to deposit from client's bank account
    * @param {string} reference - Reference for their transaction
    * @return none
    */
    void deposit (const float amount, const string& reference) {
        if (getStatus()!=0) {
            Account::deposit(amount, reference);
        } else if (getStatus()==1 && getBalance()+amount >25) {
            Account::deposit(amount, reference);
            changestatus();
        } else {
            cout << "Not enough funds to change the status of account to active!" << endl;
        }
    }
    
    /**
    * Set Service Charge for more than 4 monthly withdrawals and call Account monthly function 
    * to perform monthly cuts and addition
    */
    void monthly() {
        //monthly service charge for more than 4 withdrawals
        if (getnwithdrawal()>4) {          
            int n = getnwithdrawal() - 4;
            float amount = n * 1.0;
            setServicecharge(amount);
        }
        Account::monthly();
        //checking if this results in account going negative
        changestatus();                         
    }
};

class Checking : public Account {
public:
    Checking() {}

    explicit Checking(string acc)
    : Account(acc, true) {}

     /**
    * Deposits Money to Client's Checking Account
    * 
    * The client can deposit:
    *          1) If their bank account is active
    *          2) If their bank account is inactive but the balance, after depositing, is more than $25
    *
    * @param {float} amount - Amount to deposit from client's bank account
    * @return none
    */
    void deposit (const float amount, const string& reference) {
        if (getStatus()!=0) {
            Account::deposit(amount, reference);
        } else if (getStatus()==1 && getBalance()+amount >25) {
            Account::deposit(amount, reference);
            changestatus();
        } else {
            cout << "Not enough funds to change the status of account to active!" << endl;
        }
    }

    /**
    * Withdraws Money from Client's Checking Account
    * 
    * The client can only withdraw if the client has enough funds to cover for the service charge i.e. $15 then any transaction
    * leading to negative bank balance will set the client's bank account status to Inactive. If not, the client cannot withdraw. 
    *
    * @param {float} amount - Amount to withdraw from client's bank account
    * @return none
    */
    void withdraw(const float amount, const string reference) {
        if (getBalance() - amount < 0) {
            if (getBalance() < 15) {
                cout << "Not enough fund for service charge! Please add enough funds to have a minimum balance of $0" << endl;
            } else {
                deductServicecharge(15);
                Account::withdraw(amount, reference);
                //check if client's balance has gone negative
                changestatus();
            }
        } else {
            Account::withdraw(amount, reference);
        }
    }

    /**
    * Set monthly $5 fee and add 0.10 for each withdrawal last month. Then, calls Account monthly function 
    * to perform monthly cuts and addition
    */
    void monthly() {
        //setServicecharge(5 + (0.10 * getnwithdrawal()));
        Account::monthly();
    }
};
#endif //BANK_ACCOUNTTYPE_H
