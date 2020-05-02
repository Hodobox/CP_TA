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
    this -> location = room;
    room -> enter();
}
