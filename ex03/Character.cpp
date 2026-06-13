#include "Character.hpp"

Character::Character(std::string const & name) : _name(name), _index(0) 
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
        _inventory[i] = other._inventory[i];
        _savedMateria[i] = other._savedMateria[i];
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
            if (_inventory[i])
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = NULL;
            _savedMateria[i] = other._savedMateria[i];
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
    if (i == 4)
    {
        std::cout << "Returned safely for " << m->getType() << std::endl;
        return ;
    }
    _index = i;
    _inventory[i] = m;
    _index++;
}

void Character::unequip(int idx)
{
    int i = 0;
    int j = 0;
    while (_savedMateria[i])
      i++;
    _savedMateria[i] = _inventory[idx];
    _inventory[idx] = 0;
    i = 0;
    while (i < _index)
    {
        if (idx != i)
        {
            _inventory[j] = _inventory[i]->clone();
            j++;
        }
        i++;
    }
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
    while (i < _index)
    {
        delete(_inventory[i]);
        i++;
    }
    i = 0;
    while (_savedMateria[i])
    {
        delete(_savedMateria[i]);
        i++;
    }

}
