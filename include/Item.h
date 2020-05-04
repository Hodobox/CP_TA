#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Player;
class Room;
class Level;

class Item
{
    public:
        Item(string name);
        virtual ~Item();
        virtual bool on_pickup() const {return true;}; // return value is 'continue with default behaviour in game loop?'
        virtual bool on_drop() const {return true;};

        string name;

        bool operator<(const Item &i) const
        {
            return this -> name < i.name;
        }

        struct ItemPtrCmp
        {
          bool operator()(const Item* lhs, const Item* rhs) const  { return lhs->name < rhs->name; };
        };

    protected:

    private:
};

class DeathOnPickupItem : public Item
{
    public:
        DeathOnPickupItem(string name, string death_msg, Level *level) : Item(name) {this->death_msg = death_msg; this->level = level;};
        string death_msg;
        Level *level;
        bool on_pickup() const override;
};

class InfiniteLoopItem : public Item
{
    public:
        InfiniteLoopItem(string name) : Item(name) {};
        bool on_pickup() const override;
};

void add_item(Player *p, Item* i);
void add_item(Room *r, Item* i);

#endif // ITEM_H
