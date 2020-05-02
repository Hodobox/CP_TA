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
        Player *player = nullptr;

        void play();
        bool complete = false;


    protected:

    private:

};

Room* create_room(Level *L, string room_name, string room_desc);

#endif // LEVEL_H
