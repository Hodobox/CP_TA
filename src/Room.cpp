#include "Room.h"
#include "Level.h"


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

bool Room::enter()
{
    cout << enter_desc << "\n";
    this -> list_neighbors();
    return true;
}

void Room::list_neighbors()
{
    cout << "You can go:\n";
    for(int i=0;i<(int)this->neighbors.size();++i)
    {
        if( this -> neighbors[i] == nullptr ) continue;
        cout << dir_names[i] << " to " << (this -> neighbors[i] -> name) << "\n";
    }
}

bool make_neighbors(Room *first, Room* second, int direction)
{
    int opp_direction = (direction+2)%4;

    if(first->neighbors[direction] != nullptr) return false;
    if(second->neighbors[opp_direction] != nullptr) return false;
    first->neighbors[direction] = second;
    second->neighbors[opp_direction] = first;
    return true;
}

bool FinishRoom::enter()
{
    cout << enter_desc << "\n";
    this -> level -> complete = true;
    return true;
}
