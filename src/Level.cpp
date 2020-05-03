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
    cout << "\n";
    player -> list_inventory();
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

        vector<string> tokens;
        string tmp;
        for(char c : response)
        {
            if(c==' ')
            {
                if(!tmp.empty()) tokens.push_back(tmp);
                tmp = "";
            }
            else tmp += c;
        }
        if(!tmp.empty()) tokens.push_back(tmp);

        if(tokens.size() >= 2)
        {
            string item_name;
            for(int i=1;i<(int)tokens.size();++i)
            {
                if(!item_name.empty()) item_name += " ";
                item_name += tokens[i];
            }

            if(tokens[0] == "take")
            {
                done = true;
                auto it = player -> location -> items.find(Item(item_name));
                if(it == player -> location -> items.end())
                {
                    cout << "You attempt to take " << item_name << ", even though it doesn't exist. Maybe you should try something else.\n";
                }
                else
                {
                    player -> inventory.insert(*it);
                    player -> location -> items.erase(it);
                    cout << "You take the " << item_name << ".\n";
                }
            }
            else if (tokens[0] == "drop")
            {
                done = true;
                auto it = player -> inventory.find(Item(item_name));
                if(it == player -> inventory.end())
                {
                    cout << "You attempt to drop " << item_name << ", even though you don't have such a thing. Maybe you should try something else.\n";
                }
                else
                {
                    player -> location -> items.insert(*it);
                    player -> inventory.erase(it);
                    cout << "You drop the " << item_name << ".\n";
                }
            }
        }

        if(done) continue;

        cout << response << " is not an action you can take.\n";
        player -> location -> list_neighbors();
        cout << "\n";
        player -> location -> list_items();
        if(player -> location -> items.size()) cout << "\n";
        player -> list_inventory();
     }
}
