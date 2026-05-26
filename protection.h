#ifndef PROTECTION_H
#define PROTECTION_H

#include <string>

class ProtectionSpell
{
private:
    std::string name; // private data member

public:
    ProtectionSpell(const std::string &spellName = "Ancestral Ward");
    std::string getName() const; // public member function
    void activate();             // public member function (easter egg effect)
    bool isActive() const;
};

#endif
