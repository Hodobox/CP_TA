#include "Player.h"

Player::Player(Room* location)
{
    //ctor
    this -> location = location;
}

Player::~Player()
{
    //dtor
}

void Player::enter(Room* room)
{
    if(room -> enter())
        this -> location = room;
}

void Player::list_inventory()
{
    if(this -> inventory.empty())
    {
        cout << "Your inventory is empty.\n";
        return;
    }

    cout << "You have the following items in your inventory:\n";
    for(Item* i : this->inventory)
        cout << i->name << "\n";
}
