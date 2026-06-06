#include "Ice.hpp"

Ice::Ice(std::string const & type) : AMateria(type), _type(type) {}

Ice::Ice(Ice const &other)
{
  _type = other._type;
}

Ice& Ice::operator=(Ice const &other)
{
  if (this != &other)
  {
    _type = other._type;
  }
  return (*this)
}

Ice::~Ice()
{
  delete()
}

