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

MateriaSource::MateriaSource(const MateriaSource &other)
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
        _templates[i] = other._templates[i];
        i++;
    }
  }
  return (*this);
}

MateriaSource::~MateriaSource() {}

void MateriaSource::learnMateria(AMateria* m)       
{
    int i = 0;
    while (i < 4)
    {
        if (!_templates[i])
        {
            _templates[i] = m->clone();
            return ;
        }
        i++;
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    if (type != "ice" && type != "cure")
        return (NULL);
    int i = 0;
    AMateria *newMateria;
    while (i < 4)
    {
        if (_templates[i])
        {
            newMateria = _templates[i]->clone();
            return (newMateria);
        }
        i++;
    }
    return (NULL);
}