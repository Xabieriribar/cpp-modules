#include "Character.hpp"

Character::Character() : ICharacter() 
{
    int i = 0;
    while (i < 4)
    {
        _inventory[i] = NULL;
        i++;
    }
}

Character::Character(const Character &other) : ICharacter(other) 
{
    int i = 0;
    while (i < 4)
    {
        _inventory[i] = other._inventory[i];
        i++;
    }
}

Character& Character::operator=(const Character &other) 
{
    if (this != &other)
    {
        int i = 0;
        while (i < 4)
        {
            ICharacter::operator=(other);
            _inventory[i] = other._inventory[i];
            i++;
        }
    }
    return (*this);
}

Character::~Character() {} 

void Character::equip(AMateria* m)
{
    int i = 0;
    while (i < 4)
    {
        if (!_inventory[i])
        {
            _inventory[i] = m;
            return ;
        }
        i++;
    }

}
void Character::unequip(int idx)
{
    int i = 0;
    while (i < 4)
    {
        if (!_inventory[i])
        {
            _inventory[i] = m;
            return ;
        }
        i++;
    }
}
void Character::use(int idx, ICharacter& target)
{

}