#include <iostream>
#include "Level.h"
#include "Room.h"
using namespace std;

void demo()
{
    cout << "setting up demo\n";
    Level L = Level("demo");
    Room* start = create_room(&L, "start", "You wake up in a cell.");
    Room* finish = create_room(&L, "finish", "You arrive outside. Freedom at last!");
    make_neighbors(start, finish, east);
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
