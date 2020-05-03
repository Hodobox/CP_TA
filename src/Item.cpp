#include "Item.h"

#include "Player.h"
#include "Room.h"
#include "Level.h"

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

bool DeathOnPickupItem::on_pickup() const
{
    cout << this -> death_msg << "\n";
    this -> level -> lost = true;
    return false;
}
