#include "AMateria.hpp"

AMateria::AMateria(std::string const & type) : _type(type) {}

AMateria::AMateria() : _type(NULL) {}

AMateria::AMateria(const AMateria &other)
{
  _type = other._type;
}

AMateria& AMateria::operator=(const AMateria &other)
{
  if (this != &other)
  {
    _type = other._type;
  }
  return (*this)
}

AMateria::~AMateria() {}

std::string const & AMateria::getType() const
{
  return (_type); 
}

virtual void use(ICharacter& target);
