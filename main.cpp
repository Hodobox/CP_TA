#include <iostream>
#include <queue>
#include <vector>
#include <map>

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
    add_item(vault, new InfiniteLoopItem("infinite loop","You take the infinite loop."));

    L.play();

    if(L.complete) cout << "OK\n";
    else cout << "WA\n";
}

void maze(int N = 30)
{
    Level L = Level("maze");
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

void collector()
{
    vector<string> prefixes = {"statue of a ","painting of a ","portrait of a ","ancient book about a ","photograph of a ","a meme about a ","a life-sized model of a ","a miniature model of a "};
    vector<string> subjects = {"banana","handsome young man","dog","child","house","pretty young woman"};
    map<string,vector<string> > adjectives;
    adjectives["banana"] = {"yellow","green","tasty-looking","peeled"};
    adjectives["handsome young man"] = {"barely dressed","dancing,","single,"};
    adjectives["dog"] = {"fluffy","happy","sleeping"};
    adjectives["child"] = {"bored","bent-over","playing"};
    adjectives["house"] = {"stone","wooden","burning","green"};
    adjectives["pretty young woman"] = adjectives["handsome young man"];

    set<string> created_items;
    map<string,Item*> item_ptrs;
    int collectable = 0;

    Level L = Level("collector");

    for(string adj : adjectives["house"])
    {
        string house_name = "a life-sized model of a " + adj + " house";
        created_items.insert(house_name);
        item_ptrs[house_name] = new DeathOnPickupItem(house_name,"After four days of trying to fit " + house_name + " into your backpack, you die of exhaustion.", &L);
    }

    created_items.insert("a meme about a barely dressed handsome young man");
    item_ptrs["a meme about a barely dressed handsome young man"] = new InfiniteLoopItem("a meme about a barely dressed handsome young man","SAUCE?");
    created_items.insert("a meme about a barely dressed pretty young woman");
    item_ptrs["a meme about a barely dressed pretty young woman"] = new InfiniteLoopItem("a meme about a barely dressed pretty young woman","SAUCE?");

    created_items.insert("a life-sized model of a single, handsome young man");
    item_ptrs["a life-sized model of a single, handsome young man"] = new DeathOnPickupItem("a life-sized model of a single, handsome young man","You try to pick up the single, handsome man. He turns you down. You fall into depression and have no motivation to continue doing whatever it is you should be doing.",&L);
    created_items.insert("a life-sized model of a single, pretty young woman");
    item_ptrs["a life-sized model of a single, pretty young woman"] = new DeathOnPickupItem("a life-sized model of a single, pretty young woman","You try to pick up the single, pretty woman. She turns you down. You fall into depression and have no motivation to continue doing whatever it is you should be doing.",&L);

    created_items.insert("photograph of a bent-over child");
    item_ptrs["photograph of a bent-over child"] = new DeathOnPickupItem("photograph of a bent-over child","You take the photograph of a bent-over child. You hear sirens in the distance.\nMaybe you should be more subtle about your preferences next time.\nFBI OPEN UP!!!",&L);

    created_items.insert("a life-sized model of a bent-over child");
    item_ptrs["a life-sized model of a bent-over child"] = new DeathOnPickupItem("a life-sized model of a bent-over child","As you struggle with the life-sized model of a bent-over child, your phone falls out of your pocket, taking a picture of you behind the child, and sending it to your crush. You die of shame.", &L);

    created_items.insert("infinite loop");
    item_ptrs["infinite loop"] = new InfiniteLoopItem("infinite loop","You take the infinite loop.");

    created_items.insert("ancient book about demonic rituals");
    item_ptrs["ancient book about demonic rituals"] = new DeathOnPickupItem("ancient book about demonic rituals","As you take the ancient book about demonic rituals, you cut yourself on a particularly sharp page. The blood seeps into the pages. Oh no, you have summoned Cthulhu, the destroyer of worlds. Praise be upon him!",&L);

    created_items.insert("the flight about to depart to Las Vegas");
    item_ptrs["the flight about to depart to Las Vegas"] = new DeathOnPickupItem("the flight about to depart to Las Vegas","You take the flight about to depart to Las Vegas. You lose your return ticket in a casino. Hmm, now what.",&L);

    Condition* collector_condition = new Condition(&L,"item quota");

    for(string pref : prefixes)
    {
        for(string subj : subjects)
        {
            for(string adj : adjectives[subj])
            {
                string item_name = pref + adj + " " + subj;
                if(created_items.find(item_name) != created_items.end()) continue;

                created_items.insert(item_name);
                item_ptrs[item_name] = new Item(item_name);
                collectable++;
                BaseCondition* cond = new RoomHasItemCondition(&L, item_name + " Museum lobby", "Museum lobby", item_name);
                collector_condition -> add_condition(cond);
            }
        }
    }

    int N = 0;
    while(N*N-1<(int)created_items.size()) ++N;

    vector<vector<string> > layout(N,vector<string>(N,""));
    layout[0][0] = "Museum lobby";
    create_room<Room>(&L, "Museum lobby","You head into the museum lobby.");
    for(int i=0;i<N;++i)
    for(int k=0;k<N;++k)
    {
        if(!i && !k) continue;
        layout[i][k] = "Museum room " + to_string(i) + "," + to_string(k);
        string desc = "You enter Museum room " + to_string(i) + "," + to_string(k);
        create_room<Room>(&L,layout[i][k], desc);
    }

    srand(time(0));

    for(string item_name : created_items)
    {
        int x = rand() % N, y = rand() % N;
        while(!x && !y) x = rand() % N, y = rand() % N;
        add_item(L.rooms[layout[x][y]], item_ptrs[item_name]);
    }

    int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
    for(int i=0;i<N;++i)
    for(int k=0;k<N;++k)
    {
        for(int d=0;d<4;++d)
        {
            int ni = i + dx[d];
            int nk = k + dy[d];
            if(ni<0||nk<0||ni==N||nk==N) continue;
            make_neighbors(L.rooms[layout[i][k]],L.rooms[layout[ni][nk]],d);
        }
    }

    create_room<FinishRoom>(&L,"Museum exit","Your boss finally lets you out of the bloody museum");
    make_neighbors(L.rooms["Museum exit"],L.rooms["Museum lobby"],east);
    L.rooms["Museum exit"] -> requirements_failed_msg = "Hey, where are you going? You've been hired at minimum wage to help move out our exhibits! I'm not letting you leave until I see " + to_string(collectable) + " exhibits packed up neatly in the lobby! Now get moving!";
    L.rooms["Museum exit"] -> condition = collector_condition;

    L.player = new Player(L.rooms["Museum lobby"]);
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
    cout << "2 for collector\n";
    string s;
    getline(cin,s);

    /*try {
        choice = stoi(s);
    }
    catch (const exception &e)
    {
        cerr << e.what() << "\n";
        return 0;
    }*/

    if(!choice) demo();
    else if(choice==1) maze();
    else collector();

    return 0;
}
