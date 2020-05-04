#include <iostream>
#include "Level.h"
#include "Room.h"
using namespace std;

void demo()
{
    cout << "setting up demo\n";
    Level L = Level("demo");
    Room* start = create_room<Room> (&L, "cell", "You wake up in a cell.");
    Room* middle = create_room<Room>(&L, "hallway", "You enter the dimly-lit hallway.");
    Room* vault = create_room<Room>(&L, "vault","You peek inside the vault. There are warning signs in a langue you can't read.");
    FinishRoom* finish = create_room<FinishRoom>(&L, "dungeon exit", "You arrive outside. Freedom at last!");

    BaseCondition* torch_in_hallway = new PlayerHasItemCondition(&L, "torch hallway","torch");
    middle->condition = torch_in_hallway;

    BaseCondition* key_for_exit = new PlayerHasItemCondition(&L, "key dungeon exit","key",true);
    finish->condition = key_for_exit;

    middle -> requirements_failed_msg = "The hallway is very dark. You stub your toe on a corner and hop back into your cell, cursing. You wish you never left it.";
    finish -> requirements_failed_msg = "The exit is locked!";

    make_neighbors(start, middle, east);
    make_neighbors(middle, finish, south);
    make_neighbors(middle, vault, east);
    L.player = new Player(start);

    add_item(L.player, new Item("broken shackles"));
    add_item(middle, new Item("key"));
    add_item(start, new Item("torch"));
    add_item(middle, new DeathOnPickupItem("rat poison","Not quite sure why yourself, you take the rat poison. Surprisingly, even though you are most definitely not a rat, it poisons you. You die.", &L));
    add_item(vault, new InfiniteLoopItem("infinite loop"));

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
