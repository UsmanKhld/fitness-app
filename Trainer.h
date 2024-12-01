#ifndef TRAINER_H
#define TRAINER_H

#include <string>

using namespace std;

class Trainer
{
private:
    string filename;

public:
    Trainer(const string &filename);
    void trainerOptions();
    void viewUsers();
    void addWorkout();
};

#endif
