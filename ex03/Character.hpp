#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Character : public ICharacter I
{
  private:
    AMateria inventory[4];
  public:
    Character(); 
    Character(const Character &other); 
    operator=(const Character &other); 
    ~Character() 
};

#endif
