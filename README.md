
# Bank-Program

## Table of Content

- [Bank-Program](#bank-program)
  * [About](#about)
  * [Setup and Deployment](#setup-and-deployment)
    + [Navigate to the code directory](#navigate-to-the-code-directory)
    + [Compile the program](#compile-the-program)
    + [Execute the program](#execute-the-program)
  * [Features](#features)
    + [Register a Client](#register-a-client)
    + [Client Transaction](#client-transaction)
    + [Get Client Detail](#get-client-detail)
    + [Close Account](#close-account)
    + [Soon to be Added](#soon-to-be-added)
  * [Example Bank Statement](#example-bank-statement)

## About
A simple banking program to register clients and carry out bank transaction. Bank accounts are saved as a file and the account details is loaded every time user wants to view summary or carry out transaction. The file is a bank statement named as bank account number which contains all the transaction details from the starting to the end with summary at the end.

## Setup and Deployment

Before compiling the program, make sure you have the GNU C++ Compiler (g++) installed on your local machine.

Download the files, from the GitHub repository, to your Desktop in a folder called Bank and then open your terminal. 

### Navigate to the code directory
```console
foo@bar:~$ cd ~/Desktop/Bank-Program/src
```

### Compile the program
```console
foo@bar src:~$ g++ --std=c++11 main.cpp -o output
```
### Execute the program
```console
foo@bar src:~$ ./output
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

```console
Are you sure you want to register an account?
Enter 1 for Yes or any other number for No:1
1) Automatic Bank Number
2) Enter Custom Bank Number
Please enter your selection: 1

Enter First Name: Prashiddha Dhoj
Enter Last Name: Thapa
Enter 1 to create Savings Account and 2 to create Current Account
Please enter your selection: 1

Client is registered with us and client's Bank ID is 2.
Enter Starting Balance: 40000
Enter interest rate for this account type: 3
```
  
### Client Transaction

The user can perform transactions on the client account. This includes depositing, withdrawing and handling monthly cuts and addition to the account. Each transaction can have a reference which will show up in the bank statement.

```console
Enter bank account number: 1
Account found!
Successfully Read Account Details
1) Deposit 
2) Withdraw 
3) Monthly 
4) Go Back 
5) Exit
Please enter your selection:
```
  
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

## Example Bank Statement

``` 
First Name: Prashiddha Dhoj, Last Name: Thapa

Thu Feb  4 09:35:25 2021
+$500.000000
Reference: Starting Deposit
-------------------

Thu Feb  4 09:35:58 2021
-$108.000000
Reference: Health Insurance (TK)
--------------------------

Thu Feb  4 09:36:14 2021
+$1500.000000
Reference: Internship Income
-------------------

Thu Feb  4 09:36:49 2021
-$895.000000
Reference: Samsung Note 20 Ultra 5G
--------------------------

Summary of Account:
Account Type: Savings
Balance: $997
Interest Rate: 5%
Number of deposits this month: 2
Number of withdrawals this month: 2
Status: Active
``` 
