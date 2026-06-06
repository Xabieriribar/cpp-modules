#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>

class AMateria
{
  protected:
    std::string const type;
  public:
  AMateria(std::string const & type);
  AMateria(AMateria const &other);
  operator=(AMateria const &other);
  ~AMateria();
  std::string const & getType() const; //Returns the materia type
  virtual AMateria* clone() const = 0;
  virtual void use(ICharacter& target);
};
#endif
