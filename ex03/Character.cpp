#include "Character.hpp"

Character::Character(std::string const & name) : _name(name) 
{
    int i = 0;
    while (i < 4)
    {
        _inventory[i] = NULL;
        _savedMateria[i] = NULL;
        i++;
    }
}

Character::Character(const Character &other) : ICharacter(other), _name(other._name), _index(other._index) 
{
    int i = 0;
    while (i < 4)
    {
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();
        else
            _inventory[i] = NULL;
        if (other._savedMateria[i])
            _savedMateria[i] = other._savedMateria[i]->clone();
        else
            _savedMateria[i] = NULL;
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
            if (other._inventory[i])
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = NULL;
            if (other._savedMateria[i])
                _savedMateria[i] = other._savedMateria[i]->clone();
            else
                _savedMateria[i] = NULL;
            _name = other._name;
            i++;
        }
    }
    return (*this);
}

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
    if (idx < 0 || idx > 3)
        return ;
    if (!_inventory[idx])
        return ;
    while (_savedMateria[i])
      i++;
    std::cout << "Saved materia index: " << i << std::endl;
    _savedMateria[i] = _inventory[idx];
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
    i = 0;
}
