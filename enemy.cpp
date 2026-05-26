#include "enemy.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

Enemy::Enemy(const std::string &enemyName) : name(enemyName)
{
    // seed random once
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

void Enemy::encounter(Player &player)
{
    std::cout << "\n🧌 A vicious " << name << " leaps from the shadows!\n";
    std::cout << "It snarls and tries to steal your relics and your life!\n";

    // 60% chance the dwarf attacks successfully
    if (std::rand() % 5 < 3)
    {
        std::cout << "The dwarf attacks!\n";
        player.takeDamage();
    }
    else
    {
        std::cout << "You outmaneuver the dwarf and defeat it!\n";
        player.defeatEnemy();
    }

    // Small chance to steal an item (but only if player has one)
    if (std::rand() % 4 == 0)
    {
        std::cout << "The dwarf tried to steal something... but your protection held!\n";
    }
}
