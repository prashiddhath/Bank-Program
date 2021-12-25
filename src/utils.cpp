using namespace std;

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
 * Finds valid account number for new client
 *
 * The function first asks user to set their bank account either automatically or manually.
 * If the user can choose from:
 *           Automatic Bank Number:
 *              Returns the lowest available bank id
 * 
 *           Custom Bank Number:
 *              The user is required to enter a bank account number. If the entered 'id' is a number and isn't already taken, then
 *              the client's desired id is returned
 *
 * @param none
 * @return {string} 'id' - valid bank account number for a newly registered client
 */
string findAccountNumber() {                                                        
    int i;
    while (true) {
        cout << "1) Automatic Bank Number\n2) Enter Custom Bank Number" << endl;
        i = takeInput("Please enter your selection: ");
        string id;
        if (i == 1) {         
            //sequential numbering system                                                      
            for (int j=1;;j++) {
                id = to_string(j);
                if (checkAvailability(id)) {
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
                //checking if custom bank id is already taken or not
                if (!checkAvailability(id)) {                                               
                    cout << "Please enter another id, bank ID already taken " << endl;
                    continue;
                }
                return id;
            }
        }
    }
}