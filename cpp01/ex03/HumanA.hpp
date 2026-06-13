#ifndef HUMAN_A
#define HUMAN_A

#include <iostream>
#include "Weapon.hpp"

class HumanA
{
    private:
        std::string _name;
        Weapon &_weapon;
    public:
        HumanA(std::string name, Weapon &weapon);
        void setWeapon(Weapon &weapon);
        void attack() const;
};
#endif