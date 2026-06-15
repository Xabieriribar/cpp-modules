#include "Character.hpp"

Character::Character(std::string const & name) : _name(name)
{
    int i = 0;
    while (i < 4)
    {
        _inventory[i] = NULL;
        i++;
    }
}

Character::Character(const Character &other) : ICharacter(other), _name(other._name)
{
    int i = 0;
    while (i < 4)
    {
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();
        else
            _inventory[i] = NULL;
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
            delete _inventory[i];
            if (other._inventory[i])
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = NULL;
            _name = other._name;
            i++;
        }
    }
    return (*this);
}

void Character::equip(AMateria* m)
{
    int i = 0;

    if (!m)
        return ;
    while (i < 4)
    {
        if (_inventory[i] == m)
            return ;
        i++;
    }
    i = 0;
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
    if (idx < 0 || idx > 3)
        return ;
    if (!_inventory[idx])
        return ;
    _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx > 3)
        return ;
    if (_inventory[idx])
        _inventory[idx]->use(target);
}

std::string const & Character::getName() const
{
    return (_name);
}

Character::~Character() 
{
    int i = 0;
    while (i < 4)
    {
        if (_inventory[i])
            delete(_inventory[i]);
        i++;
    }
}
