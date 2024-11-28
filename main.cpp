#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "User.h"
#include "Trainer.h"


using namespace std;

// Function to handle user signup
void signup(const string& filename) {
    string email, password, role, name;
    int age;

    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Are you signing up as a user or trainer? ";
    cin >> role;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your age: ";
    cin >> age;

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << email << "," << password << "," << role << "," << name << "," << age << "\n";
        file.close();
        cout << "Signup successful!\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}

// Function to handle login
bool login(const string& filename) {
    string email, password, line, storedEmail, storedPassword, storedRole, storedName;
    int storedAge;

    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return false;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, storedEmail, ',');
        getline(ss, storedPassword, ',');
        getline(ss, storedRole, ',');
        getline(ss, storedName, ',');
        ss >> storedAge;

        if (storedEmail == email && storedPassword == password) {
            cout << "Login successful.\n";
            if (storedRole == "user") {
                User user(email, filename);
                user.userOptions();
            } else if (storedRole == "trainer") {
                trainerOptions(filename);
            }
            return true;
        }

    }

    return false;
}

// Main function
int main() {
    const string filename = "users.csv";
    int choice = 10000;

    while (choice != 0 ) {
        cout << "1. Signup\n2. Login\n0. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            signup(filename);
        } else if (choice == 2) {
            if (login(filename)) {
                cout << "";
            } else {
                cout << "Login failed. Invalid email or password.\n";
            }
        } else if (choice == 0) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
