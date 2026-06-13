#include "Weapon.hpp"

const std::string& Weapon::getType() const
{
    return (_type);
}

void Weapon::setType(std::string newType)
{
    _type = newType;
}

Weapon::Weapon(std::string club)
{
    _type = club;
}