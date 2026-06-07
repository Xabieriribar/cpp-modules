#include "Ice.hpp"

Ice::Ice() : AMateria("Ice") {}

Ice::Ice(Ice const &other) : AMateria("Ice") {}

Ice& Ice::operator=(Ice const &other)
{
  if (this != &other)
  {
    _type = other._type;
    AMateria::operator=(other);
  }
  return (*this);
}

Ice::~Ice() {}

AMateria* Ice::clone() const
{
    AMateria *object = new Ice();

    return (object);
}
