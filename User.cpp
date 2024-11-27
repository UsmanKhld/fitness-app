#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// User options
void userOptions(const string& email, const string& filename) {
    int choice;
    cout << "Welcome! What would you like to do?\n";
    do {
        cout << "\n1. View workouts\n2. View available trainers\n3. Update your information\n0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Workouts: Push-ups, Squats, Lunges, Planks\n";
        } else if (choice == 2) {
            cout << "Available trainers: Trainer1, Trainer2, Trainer3\n";
        } else if (choice == 3) {
            updateUserInfo(email, filename);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
}

// Update user info
void updateUserInfo(const string& email, const string& filename) {
    string newName;
    int newAge;

    cout << "Enter your new name: ";
    cin.ignore();
    getline(cin, newName);
    cout << "Enter your new age: ";
    cin >> newAge;

    ifstream file(filename);
    ofstream tempFile("temp.csv");
    string line, storedEmail, storedPassword, storedRole, storedName;
    int storedAge;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, storedEmail, ',');
        getline(ss, storedPassword, ',');
        getline(ss, storedRole, ',');
        getline(ss, storedName, ',');
        ss >> storedAge;

        if (storedEmail == email) {
            tempFile << email << "," << storedPassword << "," << storedRole << "," << newName << "," << newAge << "\n";
        } else {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.csv", filename.c_str());

    cout << "Information updated successfully.\n";
}
