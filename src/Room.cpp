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
    for(Item* item : this->items)
    {
        delete(item);
    }
}

bool Room::enter()
{
    if(!check_enter_requirements())
    {
        cout << this->requirements_failed_msg << "\n";
        return false;
    }
    cout << enter_desc << "\n";
    this -> list_neighbors();
    cout << "\n";
    this -> list_items();
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

void Room::list_items()
{
    if(this->items.empty()) return;
    cout << "There are some items lying around:\n";
    for(Item* i : this -> items)
        cout << i->name << "\n";
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
    if(!check_enter_requirements())
    {
        cout << this->requirements_failed_msg << "\n";
        return false;
    }

    cout << enter_desc << "\n";
    this -> level -> complete = true;
    return true;
}

