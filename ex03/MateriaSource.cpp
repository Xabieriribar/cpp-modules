#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : IMateriaSource(), _index(0) {}

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
        _templates[i] = other._templates[i];
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
    while (i < _index)
        i++;
    _index = i;
    newMateria = _templates[i]->clone();
    _index++;
    return (newMateria);
}