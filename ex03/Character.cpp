#include "Character.hpp"

Character::Character(std::string const & name) : _name(name), _index(0) 
{
    int i = 0;
    while (i < 4)
    {
        _inventory[i] = NULL;
        i++;
    }
}

Character::Character(const Character &other) : ICharacter(other), _name(other._name), _index(other._index) 
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
            _name = other._name;
            _index = other._index;
            i++;
        }
    }
    return (*this);
}

void Character::equip(AMateria* m)
{
    int i = 0;
    while (i < _index)
        i++;
    _index = i;
    _inventory[i] = m;
    _index++;
}

void Character::unequip(int idx)
{
    int i = 0;
    int j = 0;
    AMateria *tmp;
    while (i < 4)
    {
        if (idx != i)
        {
            tmp = _inventory[j];
            _inventory[j] = _inventory[i]->clone();
            delete(tmp);
            j++;
        }
        else
            delete(_inventory[i]);
        i++;
    }
}

void Character::use(int idx, ICharacter& target)
{
    _inventory[idx]->use(target);
}

std::string const & Character::getName() const
{
    return (_name);
}

Character::~Character() 
{
    int i = 0;
    while (i < _index)
    {
        delete(_inventory[i]);
        i++;
    }

}