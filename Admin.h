#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin
{
private:
    string filename; // File to store user data

public:
    Admin(const string &filename);
    void adminOptions(); // Central function for admin options
    void viewAllUsers();
    void addUser();
    void removeUser();
};

#endif
