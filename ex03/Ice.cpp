#include "Ice.hpp"

Ice::Ice() : AMateria("Ice") {}

Ice::Ice(Ice const &other) : AMateria(other) {}

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

void Ice::use(ICharacter &target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}