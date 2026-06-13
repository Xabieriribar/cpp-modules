#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : IMateriaSource() 
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
        if (other._templates[i])
            _templates[i] = other._templates[i];
        else
            _templates[i] = NULL;
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
        if (other._templates[i])
            _templates[i] = other._templates[i];
        else
            _templates[i] = NULL;
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
    while (i < 4)
    {
        if (_templates[i] && _templates[i]->getType() == type)
        {
            newMateria = _templates[i]->clone();
            return (newMateria);
        }
        i++;
    }
    return (NULL);
}

MateriaSource::~MateriaSource()
{
    int i = 0;
    while (_templates[i])
    {
        delete(_templates[i]);
        i++;
    }
}