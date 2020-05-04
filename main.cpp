#include <iostream>
#include <queue>
#include <vector>

#include "Level.h"
#include "Room.h"


using namespace std;

void demo()
{
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

    L.play();

    if(L.complete) cout << "OK\n";
    else cout << "WA\n";
}

void maze()
{
    Level L = Level("maze");

    int N = 30;
    vector<vector<string> > layout(N,vector<string>(N,""));
    vector<vector<bool> > used(N,vector<bool>(N,false));
    vector<vector<int> > discoverer(N,vector<int>(N));
    int dx[] = {-1,0,1,0}, dy[] = {0,1,0,-1};

    queue<int> q;
    create_room<Room>(&L, "start","You arrive to the start of the maze.\n");
    L.player = new Player(L.rooms["start"]);
    layout[N/2][N/2] = "start";
    used[N/2][N/2] = true;

    for(int i=0;i<4;++i)
    {
        int nx = N/2 + dx[i];
        int ny = N/2 + dy[i];
        if(nx<0||ny<0||nx==N||ny==N) continue;
        used[nx][ny] = true;
        discoverer[nx][ny] = i;
        q.push(nx);
        q.push(ny);
    }

    vector<string> keyless_rooms = {"start"};

    cout << "here\n";

    int keynum = 0;
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        keynum++;

        for(int i=0;i<4;++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0||ny<0||nx==N||ny==N||used[nx][ny]) continue;
            used[nx][ny] = true;
            discoverer[nx][ny] = i;
            q.push(nx);
            q.push(ny);
        }

        string roomname = "room labeled " + to_string(keynum);
        string keyname = "key labeled " + to_string(keynum);
        layout[x][y] = roomname;

        if(q.empty())
        {
            create_room<FinishRoom>(&L,roomname,"You have solved the maze! Congratulations!");
        }
        else
        {
            create_room<Room>(&L,roomname,"You enter " + roomname);
        }

        int ox = x + dx[ (discoverer[x][y]+2)%4 ], oy = y + dy[ (discoverer[x][y]+2)%4 ];
        make_neighbors( L.rooms[layout[ox][oy]] ,L.rooms[roomname], discoverer[x][y]);

        BaseCondition* keycond = new PlayerHasItemCondition(&L, keyname + " " + roomname, keyname, true);
        L.rooms[roomname] -> condition = keycond;
        L.rooms[roomname] -> requirements_failed_msg = "You don't have the key for this room.";

        int where_to_put_key = rand() % keyless_rooms.size();
        swap(keyless_rooms.back(),keyless_rooms[where_to_put_key]);
        add_item(L.rooms[keyless_rooms.back()], new Item(keyname));
        keyless_rooms.pop_back();
        keyless_rooms.push_back(roomname);
    }

    L.play();

    if(L.complete) cout << "OK\n";
    else cout << "WA\n";

}

int main()
{
    int choice;
    cout << "Type:\n";
    cout << "0 for demo\n";
    cout << "1 for maze\n";
    string s;
    getline(cin,s);
    choice = stoi(s);

    if(!choice) demo();
    else maze();

    return 0;
}
