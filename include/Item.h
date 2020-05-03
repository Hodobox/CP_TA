#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Player;
class Room;

class Item
{
    public:
        Item(string name);
        virtual ~Item();

        string name;

        bool operator<(const Item &i) const
        {
            return this -> name < i.name;
        }

    protected:

    private:
};

void add_item(Player *p, Item i);
void add_item(Room *r, Item i);

#endif // ITEM_H
