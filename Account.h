#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>
#include <unistd.h>
#include <vector>
#include <cstdio>
#include <cerrno>

using namespace std;
bool transaction;
bool closing;
bool registered;

/**
 * Checks if the given account number is available or taken
 *
 * @param {string} 'idnumber' - The account number to be checked
 * @return {bool} - Returns false if the account number is taken and true if it is available
 */
bool checkAvailability(const string& idnumber) {  
    ifstream file;
    file.open(idnumber);
    if (file) {
        return false;
    }
    return true;
}

/**
 * Checks if the given string is integer or not
 *
 * @param {string} 'var' - The string to be checked
 * @return {bool} - Returns true if the string is integer else false
 */
bool isNumber(const string& var) {
    for (char i : var) {
        if ((int) i < 48 || (int) i > 57) {
            return false;
        }
    }
    return true;
}

/**
 * Displays question to the user and keeps on asking user for input until an integer is entered
 *
 * @param {string} 'question' - The question to be displayed on the console
 * @return {int} - Returns the valid input in integer
 */
int takeInput(string question){
    string i;
    while(true) {
        cout << question;
        cin >> i;
        if (isNumber(i)) {
            int ret = stoi(i);
            cin.ignore();
            return ret;
        }
        cout << "Please only enter numbers!" << endl;
    }
}

    /**
    * ... Account Class ...
    * 
    * The Account Class has objects with the basic attributes of a bank account.
    */
class Account {
private:
    float balance;
    int ndeposit, nwithdrawal;
    float interest, servicecharge;
    string fname, lname;
    int status;
    string idnumber;
    int type;

public:
    /**
    * 
    * ... Default Constructor ...
    * 
    * The user has to enter client's bank account number. If the client is already registered, then constructor loads client's account details.
    * Otherwise, "Account not registered with us" is displayed in the console
    */
    Account() {
        while (true) {
            //asks user until valid bank account number is entered                                                                              
            cout << "Enter bank account number: ";
            getline(cin, idnumber);
            if (isNumber(idnumber)) {
                break;
            }
            cout << "Wrong Entry. Please enter only numbers!" << endl;
        }
        //checks if the account exists by looking for existing data
        if (!checkAvailability(idnumber)) {                                                 
            registered = true;
            cout << "Account found!" << endl;
            ifstream file;
            file.open(idnumber);
            if (file) {
                load_account_data(file);                                                            
            } else {
                cerr << "Error reading account file!" << endl;
                exit(2);
            }
        } else {
            cout << endl << "Account not registered with us!" << endl << endl;
            registered = false;
        }
    }

    /**
    * 
    * ... Constructor ...
    * Restore client's bank account number and, if indicated, load account details
    * 
    * @param {string} 'x' - the client's account number
    * @param {bool} 'var' - indicates whether the client's account attributes is to be loaded or not
    */
    Account(string x, bool var) {
        idnumber = x;
        if (var) {
            ifstream file;
            file.open(idnumber);
            if (file) {
                load_account_data(file);
                cout << "Successfully Read Account Details" << endl;
            }
        }
    };

    /**
    * Registers a new client to the banking system. Intializes the client's account attributes, sets client's bank account number, 
    * the starting deposit and the interest rate of the client's account.
    */
    void new_account() {
        int i;
        servicecharge = 0;
        nwithdrawal = 0;
        ndeposit = 0;
        cout << "Enter First Name: ";
        getline(cin, fname);
        cout << "Enter Last Name: ";
        getline(cin, lname);
        //Write client's name to the account file
        if (!storename()) {
            cerr << "Error in writing client's name to account file (bank account)" << endl;
        }
        //Ask user to set client's account type
        while (true) {
            cout << "Enter 1 to create Savings Account and 2 to create Current Account" << endl;
            i = takeInput("Please enter your selection: ");
            if (i==1) {
                type = 1;
                break;
            }
            else if (i==2) {
                type = 2;
                break;
            }
        }
        cout << "Client is registered with us and client's Bank ID is " << idnumber << "." << endl;
        //set starting balanace
        float amount;
        string samount;
        while(true) {
            cout << "Enter Starting Balance: ";
            cin >> samount;
            if (isNumber(samount)) {
                amount = stof(samount);
                break;
            }
            cout << "Please only enter numbers!" << endl;
        }
        deposit(amount, "Starting Deposit");
        //set account interest rate
        string sinterest;
        while(true) {
            cout << "Enter interest rate for this account type: ";
            cin >> sinterest;
            if (isNumber(sinterest)) {
                interest = stof(sinterest);
                break;
            }
            cout << "Please only enter numbers!" << endl;
        }
        //set account status
        status = 1;
    }

    /**
    * 
    * Checks if the last line is from Account Summary: The last line of summary has the word Status as the first word and the program checks
    * this and determines if any transaction has been made
    * 
    * @param {ifstream} 'file' - The account file to be checked
    * @return {bool} - returns true if no transaction has been made else false
    * 
    */
    bool checkLastLine(ifstream& file) {
        vector<string> lines;                                                 
        string line;
        //stores lines from the file
        while (getline(file, line)) {
            lines.push_back(line);
        }
        bool search = true;
        char s[7] = "Status";
        for (int i = 0; i < 6; i++) {       
            //checking if the file is in format or not                                             
            if (s[i] != line[i]) {
                search = false;
            }
        }
        return search;
    }

    /**
    * 
    * Load client details from their account file (bank statement)
    * 
    * The function stores each line of the account file and, from the last line, the lines until Summary of Account are used to restore
    * the account's attributes to the Account object. The Summary of account consists of data such as Status, Balance, Interest Rate, etc. 
    * 
    * @param {ifstream} 'file' - The file from which data needs to be parsed to account attributes
    * 
    */
    void load_account_data(ifstream &nfile) {
        //checking if the file is in format or not (Account Summary at the end)
        if (!checkLastLine(nfile)) {
            cout << "File corrupt: It doesn't end with complete summary!" << endl;
            exit(3);
        }
        nfile.close();
        //opening the account file again
        ifstream file;
        file.open(idnumber);
        vector<string> lines;                                                  
        string line;
        //stores lines from the file
        while (getline(file, line)) {
            lines.push_back(line);
        }
        //delete previous Account Summary
        deletePreviousSummary(file, "Summary of Account:");
        file.close();
        //reversing the order such that last line is at pos 0
        reverse(lines.begin(), lines.end());                         
        vector<string>::iterator it;  
        it = lines.end();
        //for each line of summary, dataposition gives position from which account attribute data starts
        int dataposition[5] = {8, 16, 23, 20, 10};
        int i = -1;
        //restore client's account properties after checking each line of the account summary
        for (it = lines.begin(); it < (lines.begin() + 6); it++) {
            i++;
            switch (i) {
                case 0:
                    char sstatus[8];
                    //c_str() converts string to char array
                    sscanf((*it).c_str(), "Status: %s", sstatus);                  
                    if (sstatus[0] == 'A') {
                        status = 1;
                    } else if (sstatus[0] == 'I') {
                        status = 0;
                    } else if (sstatus[0] == 'C') {
                        status = -1;
                    }
                    else {
                        cerr << "Error reading status" << endl;
                    }
                    break;
                case 1:
                    sscanf((*it).c_str(), "Number of withdrawals this month: %i", &nwithdrawal);
                    break;
                case 2:
                    sscanf((*it).c_str(), "Number of deposits this month: %i", &ndeposit);
                    break;
                case 3:
                    sscanf((*it).c_str(), "Interest Rate: %f", &interest);
                    break;
                case 4:
                    sscanf((*it).c_str(), "Balance: $%f", &balance);
                    break;
                case 5:
                    type = 0;
                    sscanf((*it).c_str(), "Account Type: %s", sstatus);
                    //using same sstatus string to read account type
                    if (sstatus[0] == 'S') {
                        type = 1;
                    } else if (sstatus[0] == 'C') {
                        type = 2;
                    } else {
                        cerr << "Error reading bank account type" << endl;
                        exit(4);
                    }
                    break;
            }
        }
    }

    /**
    * 
    * Store the new client's name on the account file
    * 
    * @return {int} - returns 1 is the client's name has been successfully written to the file else 0
    * 
    */
    int storename() {
        ofstream file;
        file.open(idnumber);
        if (file) {
            file << "First Name: " << fname << ", " << "Last Name: " << lname << endl;
            return 1;
        }
        return 0;
    }


    /**
    * 
    * Writes deposit to the account file (bank statement)
    * 
    * @param {float} 'amount' - The amount that has been deposited
    * @param {string} 'reference' - Client's comment on the transaction
    * @return {int} - returns 1 is the transaction has been successfully written to the file else 0
    * 
    */
    int storedeposit(const float amount, const string& reference) {
        fstream file;
        string data;
        string name;
        file.open(idnumber, ios::app);
        if (file.is_open()) {
            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            data = ctime(&time);
            data.append("+$");
            data.append(to_string(amount));
            data.append("\nReference: ");
            data.append(reference);
            file << endl << data << endl;
            file << "-------------------" << endl;
            file.close();
            return 1;
        }
        return 0;
    }

    //Adds deposited amount to balance and adds transaction to the account file (bank statement)
    virtual void deposit(const float amount,const string& reference) {
        if (amount > 0) {
            balance = amount + balance;
            if (!storedeposit(amount, reference)) {
                cerr << "Error in writing transaction history to statement" << endl;
            }
            ndeposit++;
        }
    }

    /**
    * 
    * Writes withdrawal to the account file (bank statement)
    * 
    * @param {float} 'amount' - The amount that has been withdrawed 
    * @param {string} 'reference' - Client's comment on the transaction
    * @return {int} - returns 1 is the transaction has been successfully written to the file else 0
    * 
    */
    int storewithdrawal(const float amount, const string& reference) {
        fstream file;
        string data;
        file.open(idnumber, ios::app);
        if (file.is_open()) {
            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            data = ctime(&time);
            data.append("-$");
            data.append(to_string(amount));
            data.append("\nReference: ");
            data.append(reference);
            file << endl << data << endl;
            file << "--------------------------" << endl;
            file.close();
            return 1;
        }
        return 0;
    }

    //Deducts withdrawed amount from balance and adds transaction to the account file (bank statement)
    virtual void withdraw(const float amount, const string& reference) {
        if (amount > 0) {
            balance = balance - amount;
            if (!storewithdrawal(amount, reference)) {
                cerr << "Error in writing transaction history to statement" << endl;
            }
            nwithdrawal++;
        }
    }
    
    //Checks if the status of client's bank account can be changed
    void changestatus() {
        if (balance < 25) {
            status = 0;
        } else {
            status = 1;
        }
    }

    //Deduct service charge and reset number of monthly deposits and withdrawal for next month
    virtual void monthly() {
        if (servicecharge>0) {
            deductServicecharge(servicecharge);
            servicecharge = 0;
        }
        monthlyreset();
    }

    //Reset monthly deposit and withdrawal number for next month
    void monthlyreset() {
        nwithdrawal = 0;
        ndeposit = 0;
    }

    int getStatus() {
        return status;
    }

    float getBalance() {
        return balance;
    }

    int getnwithdrawal() {
        return nwithdrawal;
    }

    int getndeposit() {
        return ndeposit;
    }

    int getType() {
        return type;
    }

    float getInterest() {
        return interest;
    }

    string getID() {
        return idnumber;
    }
    
    void setServicecharge(const float amount) {
         servicecharge = servicecharge + amount;
    }

    void deductServicecharge(const float amount) {
        withdraw(amount, "Service Charge");
    }

    /**
    * 
    * Writes Account Summary to a client's account file, if any transaction has been made
    * 
    * @param {bool} 'search' - Indicates if any transaction has been made to the client's account
    * 
    */
    void writeSummary(bool search) {
        fstream file;
        file.open(idnumber, ios::app);
        if (!search) {
            file << endl << "Summary of Account:" << endl;
            file << "Account Type: ";
            if (type == 1) {
                file << "Savings" << endl;
            } else {
                file << "Current" << endl;
            }
            file << "Balance: " << "$" << balance << endl;
            file << "Interest Rate: " << interest << "%" <<endl;
            file << "Number of deposits this month: " << ndeposit << endl;
            file << "Number of withdrawals this month: " << nwithdrawal << endl;
            if (status == 1) {
                file << "Status: Active";
            } else {
                file << "Status: Inactive";
            }
        }
    }

    /**
    * 
    * Deletes Previous Summary, from a client's account file, starting from string 'start'
    * 
    * @param {ifstream} 'file' - The account file whose summary has to be deleted
    * @param {string} 'start' - Specifies from which line of the summary to delete until the end
    * 
    */
    void deletePreviousSummary(ifstream& file, string start) {
        if (transaction || closing) {
            file.clear();
            file.seekg(0);
            ofstream temp;
            temp.open("temp");
            vector<string> lines;
            if (temp) {
                string line;
                while (getline(file, line)) {
                    if (line == start) {
                        break;
                    }
                    lines.push_back(line);
                }
                vector<string>::iterator it;
                for (it = lines.begin(); it!=lines.end(); it++) {
                    if (it+1 != lines.end()) {
                        temp << *it << endl;
                        continue;
                    }
                    temp << *it;
                }
                rename("temp", idnumber.c_str());
            }
        }
    }

    /**
    * If the client wants to close their bank account then change their bank account status to Closed
    */
    void closeAccount() {
        ifstream file;
        file.open(idnumber);
        if (file) {
            if (status == 0) {
                deletePreviousSummary(file, "Status: Inactive");
            } else if (status == 1) {
                deletePreviousSummary(file, "Status: Active");
            }
            file.close();
            ofstream nfile;
            nfile.open(idnumber, ios::app);
            if (nfile) {
                nfile << endl << "Status: Closed";
                cout << endl << "Account successfully Closed!" << endl;
            }
        }
    }

    /**
    * 
    * ... Destructor ...
    * If the client's account was just now closed then no need to write summary since we already fixed it in closeAccount()
    * Otherwise, open the account file and check if the last line is from account summary or recent transaction since, for every
    * transaction, we delete the previous account summary and add transactions.
    * If the last data in file is from transaction then write an account summary
    * 
    */
    ~Account() {
        if (!closing) {
            ifstream file1;
            file1.open(idnumber);
            if (file1) {
                bool search = checkLastLine(file1);
                writeSummary(search);
            }
        }
    };
};

#endif //BANK_ACCOUNT_H
