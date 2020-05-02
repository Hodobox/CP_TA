#ifndef PLAYER_H
#define PLAYER_H

#include "Room.h"
#include "Level.h"

using namespace std;

class Player
{
    public:
        Player(Room* location);
        virtual ~Player();

        Room* location;

        void enter(Room* room);

    protected:

    private:
};

#endif // PLAYER_H
