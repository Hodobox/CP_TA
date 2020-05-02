#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Level;

class Room
{
    public:
        Room(string name);
        virtual ~Room();

        string name;

        vector<Room*> neighbors;
        Level* level;

        string enter_desc;
        bool enter();
        void list_neighbors();

    protected:

    private:
};

enum directions { north, east, south, west };
const string dir_names[4] = { "North", "East", "South", "West" };

bool make_neighbors(Room* first, Room* second, int direction);

#endif // ROOM_H
