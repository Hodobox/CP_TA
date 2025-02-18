#include "Level.h"
#include "Constants.h"
#include "Utils.h"

Level::Level(string name)
{
    // ctor
    this->name = name;
}

Level::~Level()
{
    // dtor
    delete (this->player);
    for (auto it = this->rooms.begin(); it != this->rooms.end(); it++)
    {
        delete it->second;
    }
    for (auto it = this->conditions.begin(); it != this->conditions.end(); it++)
    {
        delete it->second;
    }
}

void Level::play()
{
    cout << "-------\n";
    cout << "Welcome to level: " << name << ".\n";
    cout << "Type " << kGoCommand << " [direction] to move to an adjacent room.\n";
    cout << "Type " << kTakeCommand << " [item] to take an [item] in the room.\n";
    cout << "Type " << kDropCommand << " [item] to drop an [item] from your inventory.\n";
    cout << "Type " << kQuitCommand << " to quit.\n";
    cout << "-------\n\n";
    player->enter(player->location);
    cout << "\n";
    player->list_inventory();
    while (!(this->complete) && !(this->lost))
    {
        std::string response;
        cout << ">" << endl;
        getline(cin, response);

        auto [command, command_arg] = parse_command(response);

        if (command.empty())
        {
            cout << "No command received, try again.\n";
            continue;
        }

        if (command == kQuitCommand)
            break;

        if (command == kGoCommand)
        {
            bool done = false;
            for (int i = 0; i < 4 && !done; ++i)
            {
                if (command_arg == dir_names[i])
                {
                    if (player->location->neighbors[i] != nullptr)
                    {
                        player->enter(player->location->neighbors[i]);
                        done = true;
                    }
                }
            }

            if (!done)
            {
                cout << "You cannot go to " << command_arg << ", try again.\n";
            }
            continue;
        }

        if (command == kTakeCommand)
        {

            Item *interacted_item = new Item(command_arg);
            auto it = player->location->items.find(interacted_item);
            if (it == player->location->items.end())
            {
                cout << "You attempt to take " << interacted_item->name << ", even though it doesn't exist. Maybe you should try something else.\n";
            }
            else
            {
                if ((*(*it)).on_pickup())
                {
                    player->inventory.insert(*it);
                    player->location->items.erase(it);
                    cout << "You take the " << interacted_item->name << ".\n";
                }
            }
            continue;
        }

        if (command == kDropCommand)
        {
            Item *interacted_item = new Item(command_arg);
            auto it = player->inventory.find(interacted_item);
            if (it == player->inventory.end())
            {
                cout << "You attempt to drop " << interacted_item->name << ", even though you don't have such a thing. Maybe you should try something else.\n";
            }
            else
            {
                if ((*(*it)).on_drop())
                {
                    player->location->items.insert(*it);
                    player->inventory.erase(it);
                    cout << "You drop the " << interacted_item->name << ".\n";
                }
            }
            delete interacted_item;
            continue;
        }

        cout << command << " is not an action you can take, try again\n";
    }
}
