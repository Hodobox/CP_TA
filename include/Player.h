#ifndef PLAYER_H
#define PLAYER_H

#include "Room.h"
#include "Item.h"

#include <set>

using namespace std;

class Player
{
    public:
        Player(Room* location);
        virtual ~Player();

        Room* location;

        void enter(Room* room);
        set<Item*,Item::ItemPtrCmp> inventory;

        void list_inventory();

    protected:

    private:
};

#endif // PLAYER_H
