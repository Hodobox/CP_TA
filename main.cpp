#include <iostream>
#include "Level.h"
#include "Room.h"
using namespace std;

void demo()
{
    cout << "setting up demo\n";
    Level L = Level("demo");
    Room* start = create_room<Room> (&L, "cell", "You wake up in a cell.");
    RequireItemRoom* middle = create_room<RequireItemRoom>(&L, "hallway", "You enter the dimly-lit hallway.", "torch");
    middle -> missing_item_msg = "The hallway is very dark. You stub your toe on a corner and hop back into your cell, cursing. You wish you never left it.";
    middle -> is_permanent_unlock = false;
    Room* finish = create_room<FinishRoom>(&L, "dungeon exit", "You arrive outside. Freedom at last!");
    make_neighbors(start, middle, east);
    make_neighbors(middle,finish, south);
    L.player = new Player(start);

    add_item(L.player, Item("shackles"));
    add_item(middle, Item("key"));
    add_item(start, Item("torch"));

    cout << "finished demo setup\n";

    L.play();

    if(L.complete) cout << "OK\n";
    else cout << "WA\n";
}

int main()
{
    demo();
    return 0;
}
