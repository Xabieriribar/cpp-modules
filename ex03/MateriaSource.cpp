#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : IMateriaSource(), _index(0) 
{
    int i = 0;
    while (i < 4)
    {
        _templates[i] = NULL;
        i++;
    }
}

MateriaSource::MateriaSource(const MateriaSource &other) : IMateriaSource(other)
{
    int i = 0;
    while (i < 4)
    {
        _templates[i] = other._templates[i];
        i++;
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource &other)
{
  if (this != &other)
  {
    int i = 0;
    while (i < 4)
    {
        IMateriaSource::operator=(other);
        *(_templates[i]) = *(other._templates[i]);
        i++;
    }
  }
  return (*this);
}

void MateriaSource::learnMateria(AMateria* m)       
{
    int i = 0;
    while (i < 4)
    {
        if (!_templates[i])
        {
            _templates[i] = m->clone();
            _index++;
            delete(m);
            return ;
        }
        i++;
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    int i = 0;
    AMateria *newMateria;
    while (i < _index)
    {
        if (_templates[i]->getType() == type)
        {
            _index = i;
            newMateria = _templates[i]->clone();
            return (newMateria);
        }
        i++;
    }
    if (_templates[i]->getType() == type)
    {
        _index = i;
        newMateria = _templates[i]->clone();
        return (newMateria);
    }
    return (NULL);
}

MateriaSource::~MateriaSource()
{
    int i = 0;
    while (i < _index)
    {
        delete(_templates[i]);
        i++;
    }
}