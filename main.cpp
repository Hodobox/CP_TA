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
    Room* finish = create_room<FinishRoom>(&L, "dungeon exit", "You arrive outside. Freedom at last!");
    make_neighbors(start, middle, east);
    make_neighbors(middle,finish, south);
    L.player = new Player(start);
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
