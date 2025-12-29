
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Class to handle Account logic
class Account {
public:
    int accountNumber;
    char name[50];
    double balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Deposit: ";
        cin >> balance;
        cout << "\nAccount Created Successfully!";
    }

    void showAccount() const {
        cout << "\nAcc No. : " << accountNumber;
        cout << "\nHolder  : " << name;
        cout << "\nBalance : " << balance;
    }
};

// Function to save a new account to the file
void writeAccount() {
    Account acc;
    ofstream outFile;
    outFile.open("bank_data.txt", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char *> (&acc), sizeof(Account));
    outFile.close();
}

// Function to show all accounts in the file
void displayAll() {
    Account acc;
    ifstream inFile;
    inFile.open("bank_data.txt", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
        acc.showAccount();
        cout << "\n-----------------------";
    }
    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n\n\t--- BANK MANAGEMENT SYSTEM ---";
        cout << "\n\t1. NEW ACCOUNT";
        cout << "\n\t2. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t3. EXIT";
        cout << "\n\tSelect Your Option (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1: writeAccount(); break;
            case 2: displayAll(); break;
            case 3: cout << "\nThanks for using the system!"; break;
            default: cout << "Invalid choice!";
        }
    } while (choice != 3);

    return 0;
}