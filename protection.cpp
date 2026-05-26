#include "protection.h"
#include <iostream>

ProtectionSpell::ProtectionSpell(const std::string &spellName)
    : name(spellName) {}

std::string ProtectionSpell::getName() const
{
    return name;
}

void ProtectionSpell::activate()
{
    std::cout << "✨ The " << name << " glows with protective ancestral energy!\n";
}

bool ProtectionSpell::isActive() const
{
    return true; // always active until used by Player
}
