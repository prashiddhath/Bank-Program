#include "Accounttype.h"
string findAccountNumber() {
    int i;
    while (true) {
        cout << "1) Automatic Bank Number\n2) Enter Custom Bank Number" << endl;
        i = takeInput();
        string id;
        if (i == 1) {
            for (int j=1;;j++) {
                id = to_string(j);
                if (checkAvailability(id)) {                                        //sequential numbering system
                    return id;
                }
            }
        }
        if (i == 2) {
            while (true) {
                cout << "Enter Bank Account Number: ";
                getline(cin,id);
                if (!isNumber(id)) {
                    cout << "Wrong Entry. Please enter only numbers!" << endl;
                    continue;
                }
                if (!checkAvailability(id)) {                                               //checking if custom bank id is already taken or not
                    cout << "Please enter another id, bank ID already taken " << endl;
                    continue;
                }
                return id;
            }
        }
    }
}

float inputAmount() {
    string amount;
    while(true) {
        cout << "Enter the amount you want to deposit: ";
        cin >> amount;
        if (isNumber(amount)) {
            cin.ignore();
            return stof(amount);
        }
        cout << "Please only enter numbers!" << endl;
    }
}

void Monthly(Account* acc) {
    float balance, interest, amount;
    balance = acc->getBalance();
    interest = acc->getInterest();
    amount = balance * (interest/100);
    acc->deposit(amount, "Monthly Interest");
    acc->monthly();
}

void showSummary(Account* acc) {
    if (!checkAvailability(acc->getID())) {
        ifstream file;
        file.open(acc->getID());
        string line;
        getline(file, line);                                //getting name of client
        cout << endl << "Summary of Account:" << endl;
        cout << line << endl;
        cout << "Account Type: ";
        if (acc->getType() == 1) {
            cout << "Savings" << endl;
        } else {
            cout << "Current" << endl;
        }
        cout << "Balance: " << "$" << acc->getBalance() << endl;
        cout << "Interest Rate: " << acc->getInterest() << "%" << endl;
        cout << "Number of deposits this month: " << acc->getndeposit() << endl;
        cout << "Number of withdrawals this month: " << acc->getnwithdrawal() << endl;
        if (acc->getStatus() == 1) {
            cout << "Status: " << "Active" << endl;
        } else {
            cout << "Status: " << "Inactive" << endl;
        }
        cout << endl;
    }
}

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
                Monthly(acc);
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
    while(i!=5) {
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
                Monthly(acc);
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
        cout << "1) Get Client Detail\n2) Client Transaction\n3) Register Client\n4) Exit" << endl;
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