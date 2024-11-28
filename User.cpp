#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

User::User(const string& email, const string& filename) : email(email), filename(filename) {}


// User options
void User::userOptions() {
    int choice;
    cout << "Welcome! What would you like to do?\n";
    do {
        cout << "\n1. View workouts\n2. View available trainers\n3. Update your information\n4. View user bio\n0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Workouts: Push-ups, Squats, Lunges, Planks\n";
        } else if (choice == 2) {
            viewTrainers();
        } else if (choice == 3) {
            updateUserInfo();
        } else if (choice == 4) {
            viewUserBio();
        } 
        else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
}

// Update user info
void User::updateUserInfo() {
    vector<string> lines;
    string line;
    
    // Read all lines from the file
    ifstream inFile(filename);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    } else {
        cout << "Unable to open file" << endl;
        return;
    }

    // Update the specific line in memory
    for (size_t i = 0; i < lines.size(); i++) {
        stringstream ss(lines[i]);
        string storedEmail;
        getline(ss, storedEmail, ',');
        
        if (storedEmail == email) {
            // Get updated information
            string newPassword, role, newName;
            int newAge;
            
            cout << "Enter new password (or press enter to keep current): ";
            cin.ignore();
            getline(cin, newPassword);
            
            cout << "Enter new name (or press enter to keep current): ";
            getline(cin, newName);
            
            cout << "Enter new age (or 0 to keep current): ";
            cin >> newAge;

            // Extract existing information
            string currentLine = lines[i];
            stringstream currentSS(currentLine);
            string currentEmail, currentPassword, currentRole, currentName;
            int currentAge;
            
            getline(currentSS, currentEmail, ',');
            getline(currentSS, currentPassword, ',');
            getline(currentSS, currentRole, ',');
            getline(currentSS, currentName, ',');
            currentSS >> currentAge;

            // Use new values if provided, otherwise keep current values
            string finalPassword = newPassword.empty() ? currentPassword : newPassword;
            string finalName = newName.empty() ? currentName : newName;
            int finalAge = newAge == 0 ? currentAge : newAge;

            // Create updated line
            stringstream updatedLine;
            updatedLine << email << "," 
                       << finalPassword << "," 
                       << currentRole << "," 
                       << finalName << "," 
                       << finalAge;
            
            lines[i] = updatedLine.str();
            break;
        }
    }

    // Write all lines back to the original file
    ofstream outFile(filename, ios::trunc);  // trunc mode overwrites the file
    if (outFile.is_open()) {
        for (const string& updatedLine : lines) {
            outFile << updatedLine << endl;
        }
        outFile.close();
        cout << "Information updated successfully!" << endl;
    } else {
        cout << "Error: Unable to write to file" << endl;
    }
}

void User::viewTrainers() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line, email, password, role, name;
    int age;

    cout << "\nList of trainers:\n";
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        getline(ss, name, ',');
        ss >> age;

        if (role == "trainer") {
            cout << "Name: " << name << ", Age: " << age << "\n";
        }
    }

    file.close();
}

void User::viewUserBio() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line, storedEmail, password, role, name;
    int age;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, storedEmail, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        getline(ss, name, ',');
        ss >> age;

        if (storedEmail == email) {
            cout << "User Info:\n";
            cout << "Email: " << storedEmail << "\n";
            cout << "Name: " << name << "\n";
            cout << "Age: " << age << "\n";
            file.close();
            return;
        }
    }

    cout << "User not found in the file.\n";
    file.close();
}
