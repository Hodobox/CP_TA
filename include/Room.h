#ifndef ROOM_H
#define ROOM_H

#include "Item.h"

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
        set<Item> items;

        vector<Room*> neighbors;
        Level* level;

        string enter_desc;
        virtual bool check_enter_requirements() { return true; }
        virtual bool enter();
        void list_neighbors();
        void list_items();


    protected:

    private:
};

enum directions { north, east, south, west };
const string dir_names[4] = { "North", "East", "South", "West" };

bool make_neighbors(Room* first, Room* second, int direction);

class RequireItemRoom: public Room
{
    public:
        RequireItemRoom(string name, string item_name) : Room(name) {this->required_item = item_name;};
        bool check_enter_requirements() override;
        bool is_open = false;
        bool is_permanent_unlock = true;
        string required_item;
        string missing_item_msg;
};

class FinishRoom : public Room
{
    public:
        FinishRoom(string name) : Room(name) {};
        bool enter() override;
};

#endif // ROOM_H
