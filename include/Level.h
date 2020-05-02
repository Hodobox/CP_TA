#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Room.h"

#include <string>
#include <iostream>

using namespace std;

class Level
{
    public:
        Level(string name);
        virtual ~Level();

        string name;
        Player player;

        void play();
        bool complete = false;

    protected:

    private:

};

#endif // LEVEL_H
