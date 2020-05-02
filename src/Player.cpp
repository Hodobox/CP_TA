#include "Player.h"

Player::Player(Room* location)
{
    //ctor
    this -> location = location;
}

Player::~Player()
{
    //dtor
}

void Player::enter(Room* room)
{
    if(room -> enter())
        this -> location = room;
}
