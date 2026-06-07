#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include "ICharacter.hpp"

class AMateria
{
  protected:
    std::string _type;
  public:
    AMateria(std::string const & type);
    AMateria();
    AMateria(const AMateria &other);
    AMateria& operator=(const AMateria &other);
    virtual ~AMateria();
    std::string const & getType() const; //Returns the materia type
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};
#endif
