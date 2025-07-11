#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) : type(t), amount(a) {}
};

class Account {
private:
    int accNumber;
    string name;
    double balance;
    stack<Transaction> history;

public:
    Account(int accNo, string custName, double initialBal) {
        accNumber = accNo;
        name = custName;
        balance = initialBal;
    }

    void deposit(double amount) {
        balance += amount;
        history.push(Transaction("Deposit", amount));
        cout << "Amount " << amount << " deposited successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance.\n";
        } else {
            balance -= amount;
            history.push(Transaction("Withdraw", amount));
            cout << "Amount " << amount << " withdrawn successfully.\n";
        }
    }

    void showDetails() {
        cout << "\n--- Account Details ---\n";
        cout << "Account Number: " << accNumber << "\n";
        cout << "Customer Name: " << name << "\n";
        cout << "Balance: " << balance << "\n";
    }

    void showHistory() {
        cout << "\n--- Transaction History ---\n";
        if (history.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        stack<Transaction> temp = history;
        while (!temp.empty()) {
            Transaction t = temp.top();
            cout << t.type << ": " << t.amount << "\n";
            temp.pop();
        }
    }
};

int main() {
    int choice, accNo = 1001;
    string name;
    double initial, amount;
    Account* user = nullptr;

    while (true) {
        cout << "\n=== BANKING SYSTEM MENU ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Account\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (user != nullptr) {
                cout << "Account already created.\n";
                break;
            }
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter initial balance: ";
            cin >> initial;
            user = new Account(accNo, name, initial);
            cout << "Account created successfully.\n";
            break;

        case 2:
            if (user == nullptr) {
                cout << "Please create an account first.\n";
                break;
            }
            cout << "Enter deposit amount: ";
            cin >> amount;
            user->deposit(amount);
            break;

        case 3:
            if (user == nullptr) {
                cout << "Please create an account first.\n";
                break;
            }
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            user->withdraw(amount);
            break;

        case 4:
            if (user) user->showDetails();
            else cout << "No account found.\n";
            break;

        case 5:
            if (user) user->showHistory();
            else cout << "No account found.\n";
            break;

        case 6:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
