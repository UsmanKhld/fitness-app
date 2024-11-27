#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Trainer options menu
void trainerOptions(const string& filename) {
    int choice;

    cout << "\nWelcome, Trainer! What would you like to do?\n";
    do {
        cout << "\n1. View all users\n0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            viewUsers(filename);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye, Trainer!\n";
}

// Function to view all users
void viewUsers(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line, email, password, role, name;
    int age;

    cout << "\nList of users:\n";
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        getline(ss, name, ',');
        ss >> age;

        if (role == "user") {
            cout << "Name: " << name << ", Age: " << age << "\n";
        }
    }

    file.close();
}
