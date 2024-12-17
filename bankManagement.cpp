#include <iostream> 
#include <fstream> 
#include <vector>  
#include <iomanip> 
#include <string>  
#include <map>     
using namespace std;


class UserAuth {
    map<string, string> users; 

    void loadUsers() {
        ifstream file("users.txt", ios::in);
        string username, password;
        while (file >> username >> password) { 
            users[username] = password;
        }
        file.close();
    }

    void saveUsers() {
        ofstream file("users.txt", ios::out | ios::trunc);
        for (const auto &user : users) {
            file << user.first << " " << user.second << endl; 
        }
        file.close();
    }

public:
    UserAuth() {
        loadUsers(); 
    }

    ~UserAuth() {
        saveUsers(); 
    }

    void registerUser() {
        string username, password;
        cout << "Enter a new username: ";
        cin >> username;
        if (users.find(username) != users.end()) { 
            cout << "Username already exists. Try a different one.\n";
            return;
        }
        cout << "Enter a new password: ";
        cin >> password;
        users[username] = password;
        cout << "Registration successful! You can now log in.\n";
    }

    bool loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (users.find(username) != users.end() && users[username] == password) { 
            cout << "Login successful!\n";
            return true;
        }
        cout << "Invalid username or password.\n";
        return false;
    }
};


class Account {
public:
    string accountNumber; 
    string accountHolderName; 
    double balance; 

    Account() {} 

    Account(string accNum, string name, double bal) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = bal;
    }

   
    void display() const {
        cout << left << setw(15) << accountNumber
             << setw(20) << accountHolderName
             << setw(10) << balance << endl;
    }
};


class Bank {
    vector<Account> accounts; 

    
    void saveToFile() {
        ofstream file("accounts.txt", ios::out | ios::trunc); 
        for (const auto &acc : accounts) {
            file << acc.accountNumber << "|" << acc.accountHolderName << "|" << acc.balance << endl; 
        }
        file.close();
    }

    void loadFromFile() {
        accounts.clear(); 
        ifstream file("accounts.txt", ios::in); 
        string line;
        while (getline(file, line)) { 
            size_t pos1 = line.find('|'); 

            size_t pos2 = line.find('|', pos1 + 1); 

            string accNum = line.substr(0, pos1); 
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1); 
            double bal = stod(line.substr(pos2 + 1)); 

            accounts.emplace_back(accNum, name, bal); 
        }
        file.close(); 
    }

public:
    Bank() {
        loadFromFile(); 
    }

    ~Bank() {
        saveToFile(); 
    }

    void createAccount() {
        string accNum, name;
        double bal;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Account Holder Name: ";
        cin.ignore(); 
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> bal; 
        accounts.emplace_back(accNum, name, bal); 
        cout << "Account created successfully!\n";
    }

   
    void displayAccounts() {
        cout << left << setw(15) << "Account No" << setw(20) << "Account Holder" << setw(10) << "Balance" << endl; 
        cout << string(45, '-') << endl; 
        for (const auto &acc : accounts) { 
            acc.display(); 
        }
    }

    void deposit() {
        string accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Amount to Deposit: ";
        cin >> amount; 

        for (auto &acc : accounts) { 
            if (acc.accountNumber == accNum) { 
                acc.balance += amount; 
                cout << "Deposit successful!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void withdraw() {
        string accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Amount to Withdraw: ";
        cin >> amount; 

        for (auto &acc : accounts) { 
            if (acc.accountNumber == accNum) { 
                if (acc.balance >= amount) { 
                    acc.balance -= amount; 
                    cout << "Withdrawal successful!\n";
                } else {
                    cout << "Insufficient balance!\n";
                }
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void deleteAccount() {
        string accNum;
        cout << "Enter Account Number to Delete: ";
        cin >> accNum; 

        for (auto it = accounts.begin(); it != accounts.end(); ++it) { 
            if (it->accountNumber == accNum) { 
                accounts.erase(it); 
                cout << "Account deleted successfully!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }
};

int main() {
    UserAuth auth; 
    int authChoice;

    
    while (true) {
        cout << "1. Register\n2. Login\nEnter your choice: ";
        cin >> authChoice;

        if (authChoice == 1) {
            auth.registerUser(); 
        } else if (authChoice == 2) {
            if (auth.loginUser()) {
                break; 
            }
        } else {
            cout << "Invalid choice!\n";
        }
    }

    Bank bank; 
    int choice; 

    do {
        
        cout << "\nBank Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.displayAccounts();
                break;
            case 3:
                bank.deposit();
                break;
            case 4:
                bank.withdraw();
                break;
            case 5:
                bank.deleteAccount();
                break;
            case 6:
                cout << "Exit.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}