#include "Item.h"

#include "Player.h"
#include "Room.h"

Item::Item(string name)
{
    //ctor
    this -> name = name;
}

Item::~Item()
{
    //dtor
}

void add_item(Player *p, Item i)
{
    p -> inventory.insert(i);
}

void add_item(Room *r, Item i)
{
    r -> items.insert(i);
}
