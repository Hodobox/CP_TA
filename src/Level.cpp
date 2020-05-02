#include "Level.h"

Level::Level(string name)
{
    //ctor
    this -> name = name;
}

Level::~Level()
{
    //dtor
}

void Level::play()
{
    cout << "Welcome to level: " << name << "\n";
    player -> enter(player -> location);
    while(!(this->complete))
    {
        string response;
        getline(cin, response);

        if(response == "quit") break;

        bool done = false;
        for(int i=0;!done && i<4;++i)
        {
            if(response == dir_names[i])
            {
                if(player -> location -> neighbors[i] != nullptr)
                {
                    player -> enter(player -> location -> neighbors[i]);
                    done = true;
                }
            }
        }
        if(done) continue;
        cout << response << " is not somewhere you can go right now.\n";
     }
}

Room* create_room(Level* L, string room_name, string room_desc)
{
    Room* room = new Room(room_name);
    room -> level = L;
    room -> enter_desc = room_desc;
    return room;
}
