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
string accountno;
bool transaction;

void error () {
    cerr << "Error " << errno << ": " << strerror(errno) << endl;
}

bool checkAvailability(const string& idnumber) {
    ifstream file;
    file.open(idnumber);
    if (file) {
        return false;
    }
    return true;
}

bool isNumber(const string& var) {
    for (char i : var) {
        if ((int) i < 48 || (int) i > 57) {
            return false;
        }
    }
    return true;
}

int takeInput(){
    string i;
    while(true) {
        cout << "Please enter your selection: ";
        cin >> i;
        if (isNumber(i)) {
            int ret = stoi(i);
            cin.ignore();
            return ret;
        }
        cout << "Please only enter numbers!" << endl;
    }
}

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
    Account() {
        while (true) {
            cout << "Enter bank account number: ";
            getline(cin, idnumber);
            if (isNumber(idnumber)) {
                break;
            }
            cout << "Wrong Entry. Please enter only numbers!" << endl;
        }
        if (!checkAvailability(idnumber)) {                                                                     //checks if the account exists by looking for existing data
            cout << "Account found!" << endl;
            ifstream file;
            file.open(idnumber);
            if (file) {
                load_account_data(file);
                accountno = idnumber;
            }
            else {
                cerr << "Error reading account file!" << endl;
                exit(2);
            }
        } else {
            cout << "Account not registered with us!" << endl << endl;
        }
    }

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

    void new_account() {
        int i;
        servicecharge = 0;
        nwithdrawal = 0;
        ndeposit = 0;
        cout << "Enter First Name: ";
        getline(cin, fname);
        cout << "Enter Last Name: ";
        getline(cin, lname);
        storename();
        while (true) {
            cout << "Enter 1 to create Savings Account and 2 to create Current Account" << endl;
            i = takeInput();
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
        status = 1;
    }

    void load_account_data(ifstream &file) {
        vector<string> lines;                                                  //stores lines from the file
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        deletePreviousSummary(file);
        reverse(lines.begin(), lines.end());                               //reversing the order such that last line is at pos 0
        vector<string>::iterator it;
        it = lines.begin();
        char s[7] = "Status";
        for (int i = 0; i < 6; i++) {                                                    //checking if the file is in format or not
            if (s[i] != (*it)[i]) {
                cout << "File corrupt: It doesn't end with complete summary!" << endl;
                exit(3);
            }
        }
        it = lines.end();
        int dataposition[5] = {8, 16, 23, 20, 10};
        int i = -1;
        for (it = lines.begin(); it < (lines.begin() + 6); it++) {
            i++;
            switch (i) {
                case 0:
                    char sstatus[8];
                    sscanf((*it).c_str(), "Status: %s", sstatus);                  //c_str() string to char array
                    if (sstatus[0] == 'A') {
                        status = 1;
                    } else if (sstatus[0] == 'I') {
                        status = 0;
                    }
                    else {
                        cerr << "Error reading status" << endl;
                        error();
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
                    if (sstatus[0] == 'S') {
                        type = 1;
                    }
                    else if (sstatus[0] == 'C') {
                        type = 2;
                    }
                    else {
                        cerr << "Error reading bank account type" << endl;
                        exit(4);
                    }
                    break;
            }
        }
    }

    int storename() {
        ofstream file;
        file.open(idnumber);
        if (file) {
            file << "First Name: " << fname << ", " << "Last Name: " << lname << endl;
        } else {
            error();
            exit(5);
        }
        return 1;
    }

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

    virtual void deposit(const float amount,const string& reference) {
        if (amount > 0) {
            balance = amount + balance;
            if (!storedeposit(amount, reference)) {
                cout << "Error in writing transaction history to statement" << endl;
                error();
            }
            ndeposit++;
        }
    }

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

    virtual void withdraw(const float amount, const string& reference) {
        if (amount > 0) {
            balance = balance - amount;
            if (!storewithdrawal(amount, reference)) {
                cout << "Error in writing transaction history to statement" << endl;
                error();
            }
            nwithdrawal++;
        }
    }

    void changestatus() {
        if (balance < 25) {
            status = 0;
        } else {
            status = 1;
        }
    }

    virtual void monthly() {
        if (servicecharge>0) {
            deductServicecharge(servicecharge);
            servicecharge = 0;
        }
        monthlyreset();
    }

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

    bool checkLastLine(ifstream& file) {
        vector<string> lines;                                                  //stores lines from the file
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        bool search = false;
        char s[7] = "Status";
        for (int i = 0; i < 6; i++) {                                                    //checking if the file is in format or not
            if (s[i] == line[i]) {
                search = true;
            }
        }
        return search;
    }

    void writeSummary(bool search) {
        fstream file;
        file.open(idnumber, ios::app);
        if (!search) {
            file << endl << "Summary of Account:" << endl;
            file << "Account Type: ";
            if (type == 1) {
                file << "Savings" << endl;
            }
            else {
                file << "Current" << endl;
            }
            file << "Balance: " << "$" << balance << endl;
            file << "Interest Rate: " << interest << "%" <<endl;
            file << "Number of deposits this month: " << ndeposit << endl;
            file << "Number of withdrawals this month: " << nwithdrawal << endl;
            if (status == 1) {
                file << "Status: " << "Active";
            } else {
                file << "Status: " << "Inactive";
            }
        }
    }

    void deletePreviousSummary(ifstream& file) {
        if (transaction) {
            file.clear();
            file.seekg(0);
            ofstream temp;
            temp.open("temp");
            if (temp) {
                string line;
                while (getline(file, line)) {
                    if(line == "Summary of Account:") {
                        break;
                    }
                    temp << line << endl;
                }
                rename("temp", idnumber.c_str());
            }
        }
    }

    ~Account() {
        ifstream file1;
        file1.open(idnumber);
        if (file1) {
            bool search = checkLastLine(file1);
            writeSummary(search);
        }
    };
};

#endif //BANK_ACCOUNT_H
