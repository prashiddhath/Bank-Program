
# Bank-Program

## About
A simple banking program to register clients and carry out bank transaction. Bank accounts are saved as a file and the account details is loaded every time user wants to view summary or carryout transaction. The file will contain all of the account owner's transaction history from the time account was registered until now.

## Setup and Deployment
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

Your terminal should now be showing the menu of the banking system:
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

The user can perform client transactions which is also stored in a file named as the client's bank ID. The file shows entire transaction history of the client along with a summary at the bottom which shows account type, current balance, interest rate, status and curent month's number of deposit and withdrawal. The user can also choose the 'Monthly' option to perform monthly cuts, interest and monthly reset to the number of withdrawal and deposit.
  
### Get Client Detail

The user can also enter a bank account number and get the client details. It shows client's name and the same summary printed at the bottom of bank statement.
 
### Close Account
  
  The user can close a bank account.
  
Features that will be added soon:

  1) Search for client using full name
