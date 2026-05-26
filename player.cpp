#include "player.h"
#include <iostream>

Player::Player(const std::string &playerName)
    : name(playerName),
      livesLeft(3),
      currentRoom(0), // HALLWAY
      hasKey(false),
      hasBook(false),
      hasHeirloom(false),
      defeatedDwarves(0),
      healthScore(100)
{
}

void Player::moveTo(int room)
{
    currentRoom = room;
}

int Player::getCurrentRoom() const
{
    return currentRoom;
}

void Player::addToInventory(const std::string &item)
{
    if (item == "key" && !hasKey)
    {
        hasKey = true;
        std::cout << "You pick up the secret key. It hums with ancestral power!\n";
    }
    else if (item == "book" && !hasBook)
    {
        hasBook = true;
        std::cout << "You take the ancient book. The pages whisper your family’s secrets...\n";
    }
    else if (item == "heirloom" && !hasHeirloom)
    {
        hasHeirloom = true;
        std::cout << "You carefully take the family heirloom. It feels warm in your hands.\n";
    }
    else
    {
        std::cout << "You don't see that item here or you already have it.\n";
    }
}

bool Player::hasTheKey() const { return hasKey; }
bool Player::hasTheBook() const { return hasBook; }
bool Player::hasTheHeirloom() const { return hasHeirloom; }

bool Player::hasAllItems() const
{
    return hasKey && hasBook && hasHeirloom;
}

void Player::displayInventory() const
{
    std::cout << "\n=== Your Inventory ===\n";
    if (hasKey)
        std::cout << "🔑 Secret Key\n";
    if (hasBook)
        std::cout << "📖 Ancient Book\n";
    if (hasHeirloom)
        std::cout << "💎 Family Heirloom\n";
    if (!hasKey && !hasBook && !hasHeirloom)
        std::cout << "Nothing yet...\n";

    std::cout << "🛡️ Protection Spells: " << protectionSpells.size() << "\n";
    std::cout << "❤️ Lives left: " << livesLeft << "/3\n";
    std::cout << "💀 Evil dwarves defeated: " << defeatedDwarves << "\n";
    std::cout << "=======================\n";
}

bool Player::isAlive() const
{
    return livesLeft > 0;
}

void Player::takeDamage()
{
    if (!protectionSpells.empty())
    {
        ProtectionSpell &spell = protectionSpells.back();
        spell.activate();
        protectionSpells.pop_back();
        std::cout << "The protection spell saved you from certain death!\n";
    }
    else
    {
        livesLeft--;
        healthScore -= 30;
        std::cout << "You were injured by the trap/dwarf! Lives left: " << livesLeft << "/3\n";
    }
}

void Player::collectSpell(const ProtectionSpell &spell)
{
    protectionSpells.push_back(spell);
    std::cout << "✨ You found and collected a powerful protection spell!\n";
}

void Player::defeatEnemy()
{
    defeatedDwarves++;
}

int Player::getDefeatedCount() const
{
    return defeatedDwarves;
}
