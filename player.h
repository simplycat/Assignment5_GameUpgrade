#ifndef PLAYER_H
#define PLAYER_H

#include "protection.h"
#include <string>
#include <vector>

class Player
{
private:
    std::string name;
    int livesLeft; // private data member (starts at 3)
    int currentRoom;
    bool hasKey;
    bool hasBook;
    bool hasHeirloom;
    std::vector<ProtectionSpell> protectionSpells;
    int defeatedDwarves; // private data member
    int healthScore;     // private data member (bonus storytelling)

public:
    Player(const std::string &playerName = "Adventurer");
    void moveTo(int room);
    int getCurrentRoom() const;
    void addToInventory(const std::string &item);
    bool hasTheKey() const;
    bool hasTheBook() const;
    bool hasTheHeirloom() const;
    bool hasAllItems() const;
    void displayInventory() const;
    bool isAlive() const;
    void takeDamage(); // public member function
    void collectSpell(const ProtectionSpell &spell);
    void defeatEnemy(); // public member function
    int getDefeatedCount() const;
};

#endif
