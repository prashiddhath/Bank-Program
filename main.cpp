#include "Accounttype.h"
string findAccountNumber() {                                                        //function call to set new client's bank account number
    int i;
    while (true) {
        cout << "1) Automatic Bank Number\n2) Enter Custom Bank Number" << endl;
        i = takeInput("Please enter your selection: ");
        string id;
        if (i == 1) {                                                               //sequential numbering system
            for (int j=1;;j++) {
                id = to_string(j);
                if (checkAvailability(id)) {
                    return id;
                }
            }
        }
        if (i == 2) {                                                               //custom bank account number
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

void Monthly(Account* acc) {                                    //adds monthly interest and makes monthly cuts from client's bank account
    float balance, interest, amount;
    balance = acc->getBalance();
    interest = acc->getInterest();
    amount = balance * (interest/100);
    acc->deposit(amount, "Monthly Interest");
    acc->monthly();
}

void showSummary(Account* acc) {                                //displays summary of client's bank account in the console
    if (!checkAvailability(acc->getID())) {
        ifstream file;
        file.open(acc->getID());
        string line;
        getline(file, line);
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
            cout << "Status: Active" << endl;
        } else if (acc->getStatus() == 0) {
            cout << "Status: Inactive" << endl;
        } else if (acc->getStatus() == -1) {
            cout << "Status: Closed" << endl;
        }
        cout << endl;
    }
}

int SavingAcc() {                                                   //Client Transaction for Savings Account
    int i = 0;
    float amount;
    string reference,id;
    Savings* acc = new Savings(accountno);
    while(i!=5) {
        cout << "1) Deposit \n2) Withdraw \n3) Monthly \n4) Go Back \n5) Exit" << endl;
        i = takeInput("Please enter your selection: ");
        switch (i) {
            case 1:
                amount = takeInput("Enter the amount: ");
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->deposit(amount, reference);
                break;
            case 2:
                amount = takeInput("Enter the amount: ");
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

int CheckingAcc() {                                                   //Client Transaction for Checkings Account
    Checking* acc = new Checking(accountno);
    int i = 0;
    float amount;
    string reference, id;
    while(i!=5) {
        cout << "1) Deposit \n2) Withdraw \n3) Monthly\n4) Go Back \n5) Exit" << endl;
        i = takeInput("Please enter your selection: ");
        switch (i) {
            case 1:
                amount = takeInput("Enter the amount: ");
                cout << "Enter reference: ";
                getline(cin, reference);
                acc->deposit(amount, reference);
                break;
            case 2:
                amount = takeInput("Enter the amount: ");
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
        cout << "1) Get Client Detail\n2) Client Transaction\n3) Register Client\n4) Close Client Account \n5) Exit" << endl;
        i = takeInput("Please enter your selection: ");
        transaction = false;
        closing = false;
        if (i == 1) {
            Account *acc = new Account();
            showSummary(acc);
            delete acc;
        }
        else if (i == 2) {
            Account *acc = new Account();
            if (registered) {
                int acctype = acc->getType();
                int accstatus = acc->getStatus();
                delete acc;                                              //deleting acc to make sure an extra summary isn't written into the statement
                transaction = true;
                if (accstatus == -1) {
                    transaction = false;
                    cout << "Account has already been closed. Cannot carryout Client transaction!" << endl;
                } else if (acctype == 2){
                    ret = CheckingAcc();
                }
                else if (acctype == 1) {
                    ret = SavingAcc();
                }
                if (ret == 1)                                           //if user chooses back then the loop is continued
                    continue;
                return 0;
            }
        }
        else if (i == 3) {
            cout << "Are you sure you want to register an account?" << endl;
            cout << "Enter 1 for Yes or any other number for No: ";
            if (takeInput("Please enter your selection: ")) {
                Account *acc = new Account(findAccountNumber(), false);                 //parameter false since we're creating a new account
                acc->new_account();
                delete acc;
            }
        }
        else if (i == 4) {
            Account *acc = new Account();
            closing = true;                                 //setting closing to true since we need to update client account status
            if (acc->getStatus() != -1) {
                acc->closeAccount();
                delete acc;
            }
            else {
                cout << "Account has already been Closed!" << endl;
            }
        }
        else if (i == 5) {                                      //terminate program
            return 0;
        }
    }
}