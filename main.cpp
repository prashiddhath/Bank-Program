#include "Accounttype.h"
int SavingAcc() {
    int i = 0;
    float amount;
    string reference,id;
    Savings* acc = new Savings(accountno);
    while(i!=5) {
        cout << "1) Deposit \n2) Withdraw \n3) Monthly \n4) Go Back \n5) Exit" << endl;
        i = takeInput();
        switch (i) {
            case 1:
                amount = inputAmount();
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->deposit(amount, reference);
                break;
            case 2:
                amount = inputAmount();
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->withdraw(amount,reference);
                break;
            case 3:
                Monthly(acc, 1);
                break;
            case 4:
                delete acc;
                return 1;
        }
    }
    delete acc;
    return 0;
}

int CheckingAcc() {
    Checking* acc = new Checking(accountno);
    int i = 0;
    float amount;
    string reference, id;
    while(i!=4) {
        cout << "1) Deposit \n2) Withdraw \n3) Monthly\n4) Go Back \n5) Exit" << endl;
        i = takeInput();
        switch (i) {
            case 1:
                amount = inputAmount();
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->deposit(amount, reference);
                break;
            case 2:
                amount = inputAmount();
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->withdraw(amount,reference);
                break;
            case 3:
                Monthly(acc, 2);
                break;
            case 4:
                delete acc;
                return 1;
        }
    }
    delete acc;
    return 0;
}

int main() {
    while (true) {
        int i;
        int ret = 1;
        cout << "1) Get Customer Detail\n2) Customer Transaction\n3) Register Client\n4) Exit" << endl;
        i = takeInput();
        transaction = false;
        if (i == 1) {
            Account *acc = new Account;
            showSummary(acc);
            delete acc;
        }
        else if (i == 2) {
            Account *acc = new Account();
            if (acc->getType()==1) {
                delete acc;                                         //deleting acc to make sure an extra summary isn't written into the statement
                transaction = true;
                ret = SavingAcc();
            } else if (acc->getType()==2){
                delete acc;
                transaction = true;
                ret = CheckingAcc();
            }
            if (ret == 1)                                           //if user chooses back then the loop is continued
                continue;
            return 0;
        }
        else if (i == 3) {
            Account *acc = new Account(findAccountNumber(), false);
            acc->new_account();
            delete acc;
        }
        else if (i == 4) {
            return 0;
        }
    }
}