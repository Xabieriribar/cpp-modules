#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Character : public ICharacter
{
  private:
    AMateria *_inventory[4];
    std::string _name;
  public:
    Character(std::string const & name); 
    Character(const Character &other); 
    Character& operator=(const Character &other); 
    ~Character(); 
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
    std::string const & getName() const;
};

#endif
