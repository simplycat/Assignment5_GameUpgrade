#include "game.h"
#include <iostream>
#include <cctype>

Game::Game() : player("Adventurer") {}

std::string Game::toLowerCase(std::string s)
{
    for (size_t i = 0; i < s.length(); ++i)
    {
        s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

std::string Game::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

void Game::showInstructions()
{
    std::cout << "\n***** Welcome to the Haunted Mansion *****\n\n";
    std::cout << "*** How to Play ***\n";
    std::cout << "Commands:\n  go North | go South | go East | go West (or just North...)\n";
    std::cout << " look          - examine surroundings\n";
    std::cout << " take key / take book / take heirloom\n";
    std::cout << " search        - look for hidden protection spells\n";
    std::cout << " inventory / inv / i   - check status\n";
    std::cout << " exit or quit  - leave the game\n";
    std::cout << "Goal: Collect the secret key, ancient book, and family heirloom.\n";
    std::cout << "Return to the Grand Hallway and go south to escape!\n";
    std::cout << "Beware evil dwarves and traps — use protection spells wisely!\n";
    std::cout << "****************************************\n\n";
}

void Game::describeRoom()
{
    int room = player.getCurrentRoom();
    std::cout << "\n";
    if (room == HALLWAY)
    {
        std::cout << "You are in the Grand Hallway.\n";
        std::cout << "The walls are covered in life-sized oil painted portraits. The walls have eyes...\n";
        if (!player.hasTheHeirloom())
        {
            std::cout << "A dazzling family heirloom rests on a mahogany side table.\n";
        }
        std::cout << "To the South is the heavy oak exit door.";
        std::cout << (doorUnlocked ? " (now unlocked).\n" : " (impossibly locked).\n");
        std::cout << "Exits: North to Library, East to Parlor, West to Dark Passage, South (exit)\n";
    }
    else if (room == LIBRARY)
    {
        std::cout << "You are in the Ancient Library.\n";
        std::cout << "Towering shelves surround you, the smell of old paper and forgotten wisdom.\n";
        if (!player.hasTheKey())
        {
            std::cout << "A curious golden key embellished with white diamonds catches the moonlight.\n";
        }
        std::cout << "Exits: South to Hallway.\n";
    }
    else if (room == PARLOR)
    {
        std::cout << "You are in the Opulent Parlor.\n";
        std::cout << "Velvet drapes hang heavy with dust. A grand piano covered in cobwebs sits silent.\n";
        if (!player.hasTheBook())
        {
            std::cout << "An ancient leather-bound book lies open on a sprawling wooden desk.\n";
        }
        std::cout << "Exits: West to Hallway.\n";
    }
    else if (room == BASEMENT)
    {
        std::cout << "You are in the Spooky Basement.\n";
        std::cout << "It's damp and cold here. The sound of dripping water and scurrying creatures fills the air.\n";
        std::cout << "Exits: East back to the Grand Hallway.\n";
    }
}

void Game::processCommand(const std::string &command)
{
    if (command.empty())
        return;
    std::string lower = toLowerCase(command);
    std::string trimmed = trim(lower);

    // NEW: Clean exit support
    if (trimmed == "quit" || trimmed == "exit")
    {
        std::cout << "\nYou decide to leave the haunted mansion... for now.\n";
        std::cout << "Thanks for playing!\n";
        quitRequested = true;
        return;
    }

    if (trimmed == "look")
    {
        describeRoom();
        return;
    }

    if (trimmed == "inventory" || trimmed == "inv" || trimmed == "i")
    {
        player.displayInventory();
        return;
    }

    if (trimmed == "search")
    {
        int room = player.getCurrentRoom();
        if (room == LIBRARY || room == PARLOR)
        {
            ProtectionSpell spell("Ancestral Ward");
            player.collectSpell(spell);
        }
        else
        {
            std::cout << "You search but find nothing useful here.\n";
        }
        return;
    }

    // Take items - strictly room-aware
    if (trimmed.find("take ") == 0)
    {
        std::string item = trim(trimmed.substr(5));
        int current = player.getCurrentRoom();

        if (item == "key" && current == LIBRARY && !player.hasTheKey())
        {
            player.addToInventory("key");
            doorUnlocked = true;
        }
        else if (item == "book" && current == PARLOR && !player.hasTheBook())
        {
            player.addToInventory("book");
        }
        else if (item == "heirloom" && current == HALLWAY && !player.hasTheHeirloom())
        {
            player.addToInventory("heirloom");
        }
        else
        {
            std::cout << "You don't see that item here or you already have it.\n";
        }
        return;
    }

    // Movement
    std::string dir = "";
    if (trimmed.find("go ") == 0)
    {
        dir = trim(trimmed.substr(3));
    }
    else if (trimmed == "north" || trimmed == "south" || trimmed == "east" || trimmed == "west" ||
             trimmed == "n" || trimmed == "s" || trimmed == "e" || trimmed == "w")
    {
        if (trimmed == "n")
            dir = "north";
        else if (trimmed == "s")
            dir = "south";
        else if (trimmed == "e")
            dir = "east";
        else if (trimmed == "w")
            dir = "west";
        else
            dir = trimmed;
    }

    if (!dir.empty())
    {
        bool moved = false;
        bool attemptingExit = false;
        int nextRoom = player.getCurrentRoom();

        if (player.getCurrentRoom() == HALLWAY)
        {
            if (dir == "north")
            {
                nextRoom = LIBRARY;
                moved = true;
            }
            else if (dir == "east")
            {
                nextRoom = PARLOR;
                moved = true;
            }
            else if (dir == "west")
            {
                nextRoom = BASEMENT;
                moved = true;
            }
            else if (dir == "south")
            {
                attemptingExit = true;
            }
        }
        else if (player.getCurrentRoom() == LIBRARY)
        {
            if (dir == "south")
            {
                nextRoom = HALLWAY;
                moved = true;
            }
        }
        else if (player.getCurrentRoom() == PARLOR)
        {
            if (dir == "west")
            {
                nextRoom = HALLWAY;
                moved = true;
            }
        }
        else if (player.getCurrentRoom() == BASEMENT)
        {
            if (dir == "east")
            {
                nextRoom = HALLWAY;
                moved = true;
            }
        }

        if (moved)
        {
            player.moveTo(nextRoom);

            if (nextRoom == BASEMENT || nextRoom == PARLOR)
            {
                Enemy dwarf;
                dwarf.encounter(player);
                if (!player.isAlive())
                {
                    isAlive = false;
                    return;
                }
            }
            describeRoom();
        }
        else if (attemptingExit)
        {
            if (player.hasAllItems() && doorUnlocked)
            {
                std::cout << "\nWith all artifacts in your possession, the door swings open...\nYou win!\n";
                gameWon = true;
            }
            else if (doorUnlocked)
            {
                std::cout << "\nThe door is unlocked, but you're missing items.\n";
            }
            else
            {
                std::cout << "\nThe heavy door is locked. Find the secret key!\n";
            }
        }
        else
        {
            std::cout << "\nYou can't go that way from here.\n";
        }
        return;
    }

    std::cout << "\nInvalid command. Try 'go [direction]', 'look', 'take [item]', 'search', 'exit', or 'quit'.\n";
}

void Game::start()
{
    std::cout << "*************************************\n";
    std::cout << " THE HAUNTED MANSION\n";
    std::cout << "A text-based adventure game.\n";
    std::cout << "**********************************\n";
    std::cout << "You wake up with amnesia in an old, haunted mansion...\n";
    std::cout << "Recover the long-lost secrets of your ancestors to escape!\n\n";

    showInstructions();
    describeRoom();

    std::string command;
    while (isAlive && !gameWon && !quitRequested)
    {
        std::cout << "\n> ";
        if (!std::getline(std::cin, command))
            break;
        processCommand(command);
    }

    if (quitRequested)
    {
        std::cout << "\n*** Thanks for playing The Haunted Mansion! ***\n";
    }
    else if (!isAlive)
    {
        std::cout << "\n***GAME OVER*** You failed your mission & did not survive.\n";
    }
    else if (gameWon)
    {
        std::cout << "\n***VICTORY!*** You escaped with all the relics. The spirits are freed!\n";
        std::cout << "Evil dwarves defeated: " << player.getDefeatedCount() << "\n";
    }
}
