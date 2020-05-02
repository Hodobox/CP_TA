#include "Room.h"
#include "Level.h"

const string Room::dir_names[4] = { "North", "East", "South", "West" };

Room::Room(string name)
{
    //ctor
    this -> name = name;
    this -> neighbors.resize(4,nullptr);
}

Room::~Room()
{
    //dtor
}

void Room::enter()
{
    cout << enter_desc << "\n";

    if(this->name == "finish") this->level->complete = true;
    else this -> list_neighbors();
}

void Room::list_neighbors()
{
    cout << "You can go:\n";
    for(int i=0;i<(int)this->neighbors.size();++i)
    {
        if( this -> neighbors[i] == nullptr ) continue;
        cout << Room::dir_names[i] << " to " << (this -> neighbors[i] -> name) << "\n";
    }
}
