#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const & type) : _type(type) {}

AMateria::AMateria() : _type("") {}

AMateria::AMateria(const AMateria &other)
{
  _type = other._type;
}

AMateria& AMateria::operator=(const AMateria &other)
{
  (void)other;
  return (*this);
}

AMateria::~AMateria() {}

std::string const & AMateria::getType() const
{
  return (_type); 
}

void AMateria::use(ICharacter &target)
{
  std::cout << target.getName() << std::endl;
}
