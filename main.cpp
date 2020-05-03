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
    FinishRoom* finish = create_room<FinishRoom>(&L, "dungeon exit", "You arrive outside. Freedom at last!", "key");
    finish -> missing_item_msg = "The exit is locked!";
    make_neighbors(start, middle, east);
    make_neighbors(middle,finish, south);
    L.player = new Player(start);

    add_item(L.player, new Item("broken shackles"));
    add_item(middle, new Item("key"));
    add_item(start, new Item("torch"));
    add_item(middle, new DeathOnPickupItem("rat poison","You take the rat poison. Surprisingly, even though you are most definitely not a rat, it poisons you. You die.", &L));

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
