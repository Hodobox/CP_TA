#include <iostream>
#include "Level.h"
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Lexicon.h"
using namespace std;

void demo()
{
    cout << "setting up demo\n";
    Level L = Level("demo");
    Room* start = new Room("start");
    Room* finish = new Room("finish");
    start -> neighbors[Room::east] = finish;
    finish -> neighbors[Room::west] = start;
    start -> enter_desc = "You wake up in a cell.";
    finish -> enter_desc = "You arrive outside. Freedom at last!";
    L.player = Player(start);
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
