
# Bank-Program

## About
A simple banking program to register clients and carry out bank transaction. Bank accounts are saved as a file and the account details is loaded every time user wants to view summary or carry out transaction. The file contains all the account owner's transaction history from the time account was registered until now.

## Setup and Deployment

Before compiling the program, make sure you have the GNU C++ Compiler (g++) installed on your local machine.

Download the files, from the GitHub repository, to your Desktop in a folder called Bank and then open your terminal. 

### Navigate to the code directory
```console
foo@bar:~$ cd ~/Desktop/Bank
```

### Compile the program
```console
foo@bar Bank:~$ g++ --std=c++11 main.cpp -o output
```
### Execute the program:
```console
foo@bar Bank:~$ ./output
```

Your terminal should now be showing the menu of the banking program:
```console
foo@bar Bank:~$ ./output
1) Get Client Detail
2) Client Transaction
3) Register Client
4) Close Client Account 
5) Exit
Please enter your selection:
```


## Features

### Register a Client

This feature can be used to register a client to the banking system. Firstly, to set the client's Bank ID, the user can choose either Custom or Automatic Numbering System.

- Custom Bank Account : If valid, the user can set the new client's bank account number as desired
- Automatic Bank Number : The program chooses the lowest possible bank account number for the new client

The program then asks for the starting balance, interest rate, first name, and last name of the client. The client can choose to open either a Checking or Savings account. Each having different service charge and withdrawal policies.
  
### Client Transaction

The user can perform transactions on the client account. This includes depositing, withdrawing and handling monthly cuts and addition to the account.
  
### Get Client Detail

The user can also enter a bank account number and get the client details. It shows client's name and a summary of their account. The account summary is displayed in the following format:

```console
Summary of Account:
First Name: Prashiddha, Last Name: Thapa
Account Type: Savings
Balance: $5600
Interest Rate: 1%
Number of deposits this month: 2
Number of withdrawals this month: 3
Status: Active
```

### Close Account
  
The user can close a client's bank account. After closing a bank account, the account can no longer carry out transaction.
  
### Soon to be Added

1) Search for client using full name
2) Deduct Service Charge each month
3) Enter decimal point numbers in inputs
