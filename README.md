# Banking and Cryptocurrency Management System

This project is a simple Banking and Cryptocurrency Management System implemented in C++. It allows users to create accounts, log in, manage their bank balance, and trade cryptocurrency.

## Features

- Create a new account
- Log in to an existing account
- Deposit money into the account
- Withdraw money from the account
- Buy cryptocurrency using the account balance
- Sell cryptocurrency and add the amount to the account balance
- View account information
- View transaction history
- Undo the last transaction
- View the list of registered users
- View the leaderboard sorted by account balance

## Classes

### Transaction

Represents a transaction with the following attributes:
- `type`: Type of the transaction (Deposit, Withdrawal, Crypto Bought, Crypto Sold)
- `amount`: Amount of money involved in the transaction

### Account

Represents a user account with the following attributes:
- `username`: Username of the account holder
- `firstName`: First name of the account holder
- `lastName`: Last name of the account holder
- `phoneNumber`: Phone number of the account holder
- `panCardNumber`: PAN card number of the account holder
- `homeAddress`: Home address of the account holder
- `password`: Password for the account
- `balance`: Bank balance of the account holder
- `cryptoBalance`: Cryptocurrency balance of the account holder
- `transactions`: Stack of transactions

Provides the following methods:
- `VerifyPassword`: Verifies the entered password
- `Deposit`: Deposits money into the account
- `Withdraw`: Withdraws money from the account
- `BuyCrypto`: Buys cryptocurrency using the account balance
- `SellCrypto`: Sells cryptocurrency and adds the amount to the account balance
- `GetAccountInformation`: Displays account information
- `AddTransaction`: Adds a transaction to the transaction stack
- `UndoLastTransaction`: Undoes the last transaction
- `DisplayTransactionHistory`: Displays the transaction history

## Functions

### DisplayRegisteredUsers

Displays the list of registered users.

### DisplayLeaderboard

Displays the leaderboard sorted by account balance.

## How to Run

1. Clone the repository.
2. Compile the `main.cpp` file using a C++ compiler.
3. Run the compiled executable.

### Example

```bash
g++ main.cpp -o banking_system
./banking_system
