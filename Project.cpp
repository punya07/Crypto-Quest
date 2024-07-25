#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

class Transaction {
public:
    string type;
    int amount;

    Transaction(string t, int a) : type(t), amount(a) {}
};

class Account {
public:
    string username;
    string firstName;
    string lastName;
    string phoneNumber;
    string panCardNumber;
    string homeAddress;
    string password;
    int balance;
    int cryptoBalance;
    stack<Transaction> transactions;

    Account(string user, string first, string last, string phone, string pan, string address, string pass)
        : username(user), firstName(first), lastName(last), phoneNumber(phone),
          panCardNumber(pan), homeAddress(address), balance(0), cryptoBalance(0), password(pass) {}

    bool VerifyPassword(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    bool Deposit(int money) {
        balance += money;
        AddTransaction("Deposit", money);
        return true;
    }

    bool Withdraw(int money) {
        if (balance >= money) {
            balance -= money;
            AddTransaction("Withdrawal", money);
            return true;
        } else {
            cout << "Insufficient balance for withdrawal." << endl;
            return false;
        }
    }

    bool BuyCrypto(int amount, int price) {
        if (balance >= amount * price) {
            balance -= amount * price;
            cryptoBalance += amount;
            AddTransaction("Crypto Bought", amount * price);
            return true;
        } else {
            cout << "Insufficient balance to buy cryptocurrency." << endl;
            return false;
        }
    }

    bool SellCrypto(int amount, int price) {
        if (amount <= cryptoBalance) {
            balance += amount * price;
            cryptoBalance -= amount;
            AddTransaction("Crypto Sold", amount * price);
            return true;
        } else {
            cout << "Cannot sell more cryptocurrency than you own. Available for sale: " << cryptoBalance << endl;
            return false;
        }
    }

    void GetAccountInformation() const {
        cout << "Account Holder: " << firstName << " " << lastName << " (" << username << ")" << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "PAN Card Number: " << panCardNumber << endl;
        cout << "Home Address: " << homeAddress << endl;
        cout << "Bank Balance: $" << balance << endl;
        cout << "Crypto Balance: " << cryptoBalance << " units" << endl;
    }

    void AddTransaction(string t, int a) {
        Transaction newTransaction(t, a);
        transactions.push(newTransaction);
    }

    void UndoLastTransaction() {
        if (!transactions.empty()) {
            Transaction t = transactions.top();
            transactions.pop();
            if (t.type == "Deposit") {
                balance -= t.amount;
            } else if (t.type == "Withdrawal") {
                balance += t.amount;
            } else if (t.type == "Crypto Bought") {
                balance += t.amount;
                cryptoBalance -= t.amount / 1; // Assuming price per unit is 1
            } else if (t.type == "Crypto Sold") {
                balance -= t.amount;
                cryptoBalance += t.amount / 1; // Assuming price per unit is 1
            }
        }
    }

    void DisplayTransactionHistory() {
        cout << "Transaction History: " << endl;
        stack<Transaction> tempStack = transactions;
        while (!tempStack.empty()) {
            Transaction t = tempStack.top();
            if (!(t.type == "Crypto Sold" && t.amount > cryptoBalance)) {
                cout << t.type << ": $" << t.amount << endl;
            }
            tempStack.pop();
        }
    }
};

void DisplayRegisteredUsers(const vector<Account>& accounts) {
    cout << "Registered Users:" << endl;
    for (const auto& account : accounts) {
        cout << "Username: " << account.username << endl;
        cout << "Name: " << account.firstName << " " << account.lastName << endl;
        cout << "Phone Number: " << account.phoneNumber << endl;
        cout << "PAN Card Number: " << account.panCardNumber << endl;
        cout << "-----------------------------" << endl;
    }
}

void DisplayLeaderboard(const vector<Account>& accounts) {
    vector<Account> sortedAccounts = accounts;
    sort(sortedAccounts.begin(), sortedAccounts.end(), [](const Account& a, const Account& b) {
        return a.balance > b.balance;
    });

    cout << "Leaderboard:" << endl;
    for (const auto& account : sortedAccounts) {
        cout << account.username << ": $" << account.balance << endl;
    }
}

int main() {
    vector<Account> accounts;

    while (true) {
        cout << "*****" << endl;
        cout << "Press 1 to create a new account" << endl;
        cout << "Press 2 to log in to an existing account" << endl;
        cout << "Press 3 to view the registered users" << endl;
        cout << "Press 4 to view the leaderboard" << endl;
        cout << "Press 5 to exit" << endl;
        cout << "*****" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter a username for the new account: ";
                string username, firstName, lastName, phoneNumber, panCardNumber, homeAddress, password;
                cin >> username;

                auto usernameExists = any_of(accounts.begin(), accounts.end(), [username](const Account& acc) {
                    return acc.username == username;
                });

                if (usernameExists) {
                    cout << "Username already exists. Please choose a different username." << endl;
                    break;
                }

                cout << "Enter your first name: ";
                cin >> firstName;

                cout << "Enter your last name: ";
                cin >> lastName;

                do {
                    cout << "Enter your phone number (10 digits): ";
                    cin >> phoneNumber;
                } while (phoneNumber.length() != 10 || any_of(phoneNumber.begin(), phoneNumber.end(), ::isalpha));

                auto phoneNumberExists = any_of(accounts.begin(), accounts.end(), [phoneNumber](const Account& acc) {
                    return acc.phoneNumber == phoneNumber;
                });

                if (phoneNumberExists) {
                    cout << "Phone number already exists. Please use a different phone number." << endl;
                    break;
                }

                cout << "Enter your PAN card number (up to 10 characters): ";
                cin >> panCardNumber;

                auto panCardExists = any_of(accounts.begin(), accounts.end(), [panCardNumber](const Account& acc) {
                    return acc.panCardNumber == panCardNumber;
                });

                if (panCardExists) {
                    cout << "PAN card number already exists. Please use a different PAN card number." << endl;
                    break;
                }

                cout << "Enter your home address: ";
                cin.ignore();
                getline(cin, homeAddress);

                cout << "Create a password: ";
                cin >> password;

                accounts.push_back(Account(username, firstName, lastName, phoneNumber, panCardNumber, homeAddress, password));

                cout << "Account created successfully!" << endl;
                break;
            }

            case 2: {
                if (accounts.empty()) {
                    cout << "No accounts exist. Create an account first." << endl;
                    break;
                }

                cout << "Enter your username: ";
                string enteredUsername;
                cin >> enteredUsername;

                auto it = find_if(accounts.begin(), accounts.end(), [enteredUsername](const Account& acc) {
                    return acc.username == enteredUsername;
                });

                if (it != accounts.end()) {
                    Account& userAccount = *it;

                    cout << "Enter your password: ";
                    string enteredPassword;
                    cin >> enteredPassword;

                    if (userAccount.VerifyPassword(enteredPassword)) {
                        int userChoice;
                        while (userChoice != 8) {
                            cout << "**" << endl;
                            cout << "Logged in as: " << enteredUsername << endl;
                            cout << "Press 1 if you want to deposit money" << endl;
                            cout << "Press 2 if you want to withdraw money" << endl;
                            cout << "Press 3 if you want to buy cryptocurrency" << endl;
                            cout << "Press 4 if you want to sell cryptocurrency" << endl;
                            cout << "Press 5 to view account information" << endl;
                            cout << "Press 6 to view transaction history" << endl;
                            cout << "Press 7 to undo last transaction" << endl;
                            cout << "Press 8 to log out" << endl;
                            cout << "**" << endl;

                            cin >> userChoice;

                            switch (userChoice) {
                                case 1: {
                                    int money;
                                    cout << "Enter the amount to deposit: $";
                                    cin >> money;
                                    userAccount.Deposit(money);
                                    cout << "Deposit successful!" << endl;
                                    break;
                                }

                                case 2: {
                                    int money;
                                    cout << "Enter the amount to withdraw: $";
                                    cin >> money;
                                    userAccount.Withdraw(money);
                                    break;
                                }

                                case 3: {
                                    int amount, price;
                                    cout << "Enter the amount of cryptocurrency to buy: ";
                                    cin >> amount;
                                    cout << "Enter the price per unit: $";
                                    cin >> price;
                                    if (userAccount.BuyCrypto(amount, price)) {
                                        cout << "Cryptocurrency bought!" << endl;
                                    } else {
                                        cout << "Insufficient balance to make the purchase." << endl;
                                    }
                                    break;
                                }

                                case 4: {
                                    int amount, price;
                                    cout << "Enter the amount of cryptocurrency to sell: ";
                                    cin >> amount;
                                    cout << "Enter the price per unit: $";
                                    cin >> price;
                                    userAccount.SellCrypto(amount, price);
                                    break;
                                }

                                case 5:
                                    userAccount.GetAccountInformation();
                                    break;

                                case 6:
                                    userAccount.DisplayTransactionHistory();
                                    break;

                                case 7:
                                    userAccount.UndoLastTransaction();
                                    cout << "Last transaction undone." << endl;
                                    break;

                                case 8:
                                    cout << "Logged out." << endl;
                                    break;

                                default:
                                    cout << "Invalid choice. Returning to the main menu." << endl;
                            }
                        }
                    } else {
                        cout << "Incorrect password. Returning to the main menu." << endl;
                    }
                } else {
                    cout << "Account not found. Please enter a valid username." << endl;
                }
                break;
            }

            case 3: {
                if (accounts.empty()) {
                    cout << "No accounts exist. Create an account first." << endl;
                } else {
                    DisplayRegisteredUsers(accounts);
                }
                break;
            }

            case 4: {
                if (accounts.empty()) {
                    cout << "No accounts exist. Create an account first." << endl;
                } else {
                    DisplayLeaderboard(accounts);
                }
                break;
            }

            case 5:
                exit(0);
                break;

            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
