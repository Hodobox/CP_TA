#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Room.h"

#include <string>
#include <iostream>
#include <map>

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

        map<string, Room*> rooms;

    protected:

    private:

};

template <class T>
T* create_room(Level* L, string room_name, string room_desc)
{
    if(L->rooms.find(room_name) != L->rooms.end()) return nullptr;

    T* room = new T(room_name);
    L->rooms[room_name] = room;
    room -> level = L;
    room -> enter_desc = room_desc;
    return room;
}
#endif // LEVEL_H
