#include "Accounttype.h"

/**
 * Adds Interest to the account
 *
 * The function should be called when it is time to add interest in client's account
 *
 * @param {Object} acc - The client's account to perform monthly operations on
 * @return none
 */
void Monthly(Account* acc) {                                 
    float balance, interest, amount;
    balance = acc->getBalance();
    interest = acc->getInterest();
    //calculating interest amount to be added in client's bank account
    amount = balance * (interest/100);
    acc->deposit(amount, "Monthly Interest");
    acc->monthly();
}

/**
 * The function displays summary of client's bank account on the console
 *
 * @param {Object} acc - The client's account whose summary has to be displayed
 * @return none
 */
void showSummary(Account* acc) {                                
    if (!checkAvailability(acc->getID())) {
        ifstream file;
        file.open(acc->getID());
        string line;
        //Get Clients Name i.e. first line of the file
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

/**
 * The function acts as a menu to perform transactions on an Account
 *
 * @param {string} accountno - The client's account number who wants to perform transaction
 * @return {int} Returns 1 if the user wants to go back to the Main Menu else returns 0 when exit is selected from the menu
 */

template <class T>
int OpenMenu(string accountno, T* acc) {                                                  
    int i = 0;
    float amount;
    string reference;

    //Keep displaying user the transaction menu until they input '5' which indicates the user wants to exit
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

/**
 * Displays Main Menu of the banking program
 *
 * @param none
 * @return {int} - returns 0 on successful termination
 */
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
                registered = false;
                int acctype = acc->getType();
                int accstatus = acc->getStatus();
                string accountno = acc->getID();
                //deleting acc since we do not need it anymore
                delete acc;                                           
                transaction = true;
                if (accstatus == -1) {
                    transaction = false;
                    cout << "Cannot carry out Client transactions on a closed account!" << endl;
                } else if (accstatus == 0) {
                    transaction = false;
                    cout <<"Account is currently inactive" << endl;
                } else if (acctype == 2){
                    Checking* acc = new Checking(accountno);
                    ret = OpenMenu(accountno, acc);
                }
                else if (acctype == 1) {
                    Savings* acc = new Savings(accountno);
                    ret = OpenMenu(accountno, acc);
                }
                //if user chooses Back from the transaction menu then the loop is continued
                if (ret == 1)                                        
                    continue;
                return 0;
            }
        }
        else if (i == 3) {
            cout << "Are you sure you want to register an account?" << endl;
            cout << "Enter 1 for Yes or any other number for No";
            int i = takeInput(":");
            if (i == 1) {
                //parameter false (Indicates: Do not load account data) since we're creating a new account
                Account *acc = new Account(findAccountNumber(), false);
                acc->new_account();
                delete acc;
            }
        }
        else if (i == 4) {
            Account *acc = new Account();
            //setting closing to true since we need to delete last line of previous summary and add Status to Closed
            closing = true;                                 
            if (acc->getStatus() != -1) {
                acc->closeAccount();
                delete acc;
            }
            else {
                cout << "Account has already been Closed!" << endl;
            }
        }
        else if (i == 5) {
             //terminate program                                     
            return 0;
        }
    }
}