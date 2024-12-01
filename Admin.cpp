#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Admin::Admin(const string &filename) : filename(filename) {}

// Admin options menu
void Admin::adminOptions()
{
    int choice;
    do
    {
        cout << "\nAdmin Options:\n";
        cout << "1. View all users\n";
        cout << "2. Add a new user\n";
        cout << "3. Remove a user\n";
        cout << "0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllUsers();
            break;
        case 2:
            addUser();
            break;
        case 3:
            removeUser();
            break;
        case 0:
            cout << "Exiting Admin Menu. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// View all users
void Admin::viewAllUsers()
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line;
    cout << "\nList of Users:\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string email, password, role, name;
        int age;

        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        getline(ss, name, ',');
        ss >> age;

        cout << "Email: " << email << ", Role: " << role << ", Name: " << name << ", Age: " << age << "\n";
    }

    file.close();
}

// Add a new user
void Admin::addUser()
{
    string email, password, role, name;
    int age;

    cout << "\nEnter new user's details:\n";
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;
    cout << "Role (user/trainer): ";
    cin >> role;
    cout << "Name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);
    cout << "Age: ";
    cin >> age;

    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open())
    {
        file << email << "," << password << "," << role << "," << name << "," << age << "\n";
        cout << "User added successfully!\n";
    }
    else
    {
        cerr << "Error: Unable to open file for writing.\n";
    }

    file.close();
}

// Remove an existing user
void Admin::removeUser()
{
    string emailToRemove;
    cout << "\nEnter the email of the user to remove: ";
    cin >> emailToRemove;

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool userFound = false;

    // Read all lines, excluding the one to remove
    while (getline(file, line))
    {
        stringstream ss(line);
        string email;
        getline(ss, email, ',');

        if (email != emailToRemove)
        {
            lines.push_back(line);
        }
        else
        {
            userFound = true;
        }
    }

    file.close();

    if (!userFound)
    {
        cout << "No user found with the email: " << emailToRemove << "\n";
        return;
    }

    // Write back remaining lines to the file
    ofstream outFile(filename, ios::trunc); // Overwrite the file
    if (outFile.is_open())
    {
        for (const string &line : lines)
        {
            outFile << line << "\n";
        }
        cout << "User removed successfully!\n";
    }
    else
    {
        cerr << "Error: Unable to open file for writing.\n";
    }

    outFile.close();
}
