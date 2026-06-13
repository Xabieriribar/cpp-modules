#ifndef HUMAN_B
#define HUMAN_B

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
    private:
        std::string _name;
        Weapon  *_weapon;
        bool    hasWeapon;
    public:
        HumanB(std::string name);
        HumanB(std::string name, Weapon *weapon);
        void setWeapon(Weapon &weapon);
        void attack();
};
#endif