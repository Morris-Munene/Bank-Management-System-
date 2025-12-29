#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Account {
public:
    int accountNumber;
    char name[50];
    char password[20];
    double balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Set Security Password: ";
        cin >> password;
        cout << "Enter Initial Deposit: ";
        cin >> balance;
        cout << "\nAccount Created Successfully!";
    }

    void showAccount() const {
        cout << "\nAcc No. : " << accountNumber;
        cout << "\nHolder  : " << name;
        cout << "\nBalance : $" << balance;
    }

    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) { balance -= amount; }
};

// Function to save a new account
void writeAccount() {
    Account acc;
    ofstream outFile("bank_data.txt", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
    outFile.close();
}

// Function to show all accounts (Admin view)
void displayAll() {
    Account acc;
    ifstream inFile("bank_data.txt", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!!";
        return;
    }
    cout << "\n\n\t--- ALL ACCOUNT HOLDERS ---\n";
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        acc.showAccount();
        cout << "\n-----------------------";
    }
    inFile.close();
}

// Function to handle login and money tasks
void handleTransaction(int accNum, int type) {
    Account acc;
    fstream file;
    bool found = false;

    file.open("bank_data.txt", ios::binary | ios::in | ios::out);
    
    while (file.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        if (acc.accountNumber == accNum) {
            char pass[20];
            cout << "Enter Password: ";
            cin >> pass;

            if (strcmp(acc.password, pass) == 0) {
                found = true;
                if (type == 1) { // Deposit
                    double amt;
                    cout << "Enter Deposit Amount: "; cin >> amt;
                    acc.deposit(amt);
                } 
                else if (type == 2) { // Withdraw
                    double amt;
                    cout << "Enter Withdrawal Amount: "; cin >> amt;
                    if (amt <= acc.balance) acc.withdraw(amt);
                    else cout << "Insufficient funds!";
                }
                else if (type == 3) { // Balance Check
                    acc.showAccount();
                }

                if (type != 3) { // Save changes if deposit/withdraw
                    int pos = (-1) * static_cast<int>(sizeof(Account));
                    file.seekp(pos, ios::cur);
                    file.write(reinterpret_cast<char *> (&acc), sizeof(Account));
                    cout << "\nUpdated Balance: $" << acc.balance;
                }
            } else {
                cout << "Wrong Password!";
                found = true;
            }
            break;
        }
    }
    file.close();
    if (!found) cout << "Account Not Found!";
}

int main() {
    int choice, accNo;
    do {
        cout << "\n\n\t--- BANK MANAGEMENT SYSTEM ---";
        cout << "\n\t1. NEW ACCOUNT";
        cout << "\n\t2. LOGIN: DEPOSIT";
        cout << "\n\t3. LOGIN: WITHDRAW";
        cout << "\n\t4. LOGIN: CHECK BALANCE";
        cout << "\n\t5. ADMIN: SHOW ALL ACCOUNTS";
        cout << "\n\t6. EXIT";
        cout << "\n\tSelect Option: ";
        cin >> choice;

        switch (choice) {
            case 1: writeAccount(); break;
            case 2: cout << "Account Number: "; cin >> accNo; handleTransaction(accNo, 1); break;
            case 3: cout << "Account Number: "; cin >> accNo; handleTransaction(accNo, 2); break;
            case 4: cout << "Account Number: "; cin >> accNo; handleTransaction(accNo, 3); break;
            case 5: displayAll(); break;
            case 6: cout << "\nGoodbye!"; break;
            default: cout << "Invalid Selection!";
        }
    } while (choice != 6);

    return 0;
}