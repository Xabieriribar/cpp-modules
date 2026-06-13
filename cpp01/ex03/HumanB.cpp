#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
    hasWeapon = false;
} 
HumanB::HumanB(std::string name, Weapon *weapon) : _name(name), _weapon(weapon) {} 

void HumanB::attack()
{
    if (!hasWeapon)
        std::cout << _name << " does not have a weapon." << std::endl;
    else
        std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
    hasWeapon = true;
    _weapon = &weapon;
    _weapon->setType(weapon.getType());
}