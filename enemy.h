#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include <string>

class Enemy
{
private:
    std::string name; // private data member

public:
    Enemy(const std::string &enemyName = "Evil Dwarf");
    void encounter(Player &player); // public member function
};

#endif
