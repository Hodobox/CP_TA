#ifndef ROOM_H
#define ROOM_H

#include "Item.h"
#include "Condition.h"

#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

class Level;

class Room
{
    public:
        Room(string name);
        virtual ~Room();

        string name;
        set<Item*,Item::ItemPtrCmp> items;

        vector<Room*> neighbors;
        Level* level;

        string enter_desc;
        BaseCondition* condition;
        virtual bool check_enter_requirements() { if(condition==nullptr) return true; return condition->evaluate(); };
        virtual bool enter();
        void list_neighbors();
        void list_items();

    protected:

    private:
};

enum directions { north, east, south, west };
const string dir_names[4] = { "north", "east", "south", "west" };

bool make_neighbors(Room* first, Room* second, int direction);

class FinishRoom : public Room
{
    public:
        FinishRoom(string name) : Room(name) {};
        bool enter() override;
};

#endif // ROOM_H
