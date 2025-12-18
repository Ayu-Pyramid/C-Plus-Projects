#include <iostream>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    double balance;

public:
    void createAccount() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin,name);

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter starting balance: ";
        cin >> balance;

        cout << "Your account was successfully created";
    }
    void deposit() {
        double amount;
        cout << "Enter the money you want to deposit: \n";
        cin >> amount;

        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid amount \n";
        }



    }
    void withdraw() {
        double amount;
        cout << "Please enter the amount you want to withdraw: ";
        cin >> amount;

        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "You have successfully withdraw money from your account";
        } else {
            cout << "You don't have sufficient balance ";
        }
    }
    void showAccount() {
        cout << "Your account name is "<< name << endl;
        cout << "Your account number is "<< accountNumber << endl;
        cout << "Your current balance is "<< balance << endl;


    }
};



int main8() {

        BankAccount account;
    int choice;

    do {
        cout << "\n---- Bank Menu ----\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Show Account Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: account.createAccount();
                break;
            case 2: account.deposit();
                break;
            case 3: account.withdraw();
                break;
            case 4: account.showAccount();
                break;
            case 5: cout << "Closing the program: \n";
                break;
            default: cout << "Please choose only between 1-5: \n";
        }


    }while (choice !=5);







    return 0;
}