#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"
#include "protection.h"
#include <string>

class Game
{
private:
    Player player;
    bool doorUnlocked = false;
    bool gameWon = false;
    bool isAlive = true;
    bool quitRequested = false; // NEW: for clean exit

    const int HALLWAY = 0;
    const int LIBRARY = 1;
    const int PARLOR = 2;
    const int BASEMENT = 3;

    std::string toLowerCase(std::string s);
    std::string trim(const std::string &str);

public:
    Game();
    void start();
    void showInstructions();
    void describeRoom();
    void processCommand(const std::string &command);
};

#endif
