#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

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

#endif // ITEM_H
