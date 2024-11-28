#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
private:
    string email;
    string filename;

public:
    User(const string &email, const string &filename);
    void userOptions();
    void updateUserInfo();
    void viewTrainers();
    void viewUserBio();
    void getWorkoutsByMuscleGroup();
};
// Function declarations for user-related operations

#endif
