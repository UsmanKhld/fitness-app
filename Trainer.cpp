#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Trainer options menu
void trainerOptions(const string &filename)
{
    int choice;

    cout << "\nWelcome, Trainer! What would you like to do?\n";
    do
    {
        cout << "\n1. View all users\n2. Add a workout\n0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            viewUsers(filename);
        }
        else if (choice == 2)
        {
            addWorkout();
        }
        else if (choice != 0)
        {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye, Trainer!\n";
}

// Function to view all users
void viewUsers(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line, email, password, role, name;
    int age;

    cout << "\nList of users:\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        getline(ss, name, ',');
        ss >> age;

        if (role == "user")
        {
            cout << "Name: " << name << ", Age: " << age << "\n";
        }
    }

    file.close();
}

void addWorkout()
{
    vector<string> muscleGroups = {"Chest", "Biceps", "Triceps", "Shoulders", "Abs", "Quads", "Calves", "Glutes", "Hamstrings"};

    // Display muscle group options
    cout << "\nSelect Muscle Group:\n";
    for (size_t i = 0; i < muscleGroups.size(); i++)
    {
        cout << i + 1 << ". " << muscleGroups[i] << endl;
    }

    int muscleChoice;
    cout << "Enter the number of the muscle group: ";
    cin >> muscleChoice;

    if (muscleChoice < 1 || muscleChoice > muscleGroups.size())
    {
        cout << "Invalid choice.\n";
        return;
    }

    string muscleGroup = muscleGroups[muscleChoice - 1];
    cin.ignore(); // Ignore the newline character left in the buffer

    // Input workout details
    string workoutName;
    int sets, reps;

    cout << "Enter the workout name: ";
    getline(cin, workoutName);

    cout << "Enter the number of sets: ";
    cin >> sets;

    cout << "Enter the number of reps: ";
    cin >> reps;

    // Append workout to the CSV file
    const string fl = "workouts.csv";
    ofstream file(fl, ios::app);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    file << muscleGroup << "," << workoutName << "," << sets << "," << reps << "\n";
    file.close();

    cout << "Workout added successfully!\n";
}