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

        enum directions { north, east, south, west };

        static const string dir_names[4];

        vector<Room*> neighbors;
        Level* level;

        string enter_desc;
        void enter();
        void list_neighbors();

    protected:

    private:
};

#endif // ROOM_H
