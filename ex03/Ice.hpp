#ifndef ICE_HPP
#define ICE_HPP

#include "Amateria.hpp"

class Ice : public Amateria
{
  public:
    Ice();
    Ice(const Ice &other);
    operator=(const Ice &other);
    ~Ice();
    AMateria* clone() const;





}
#endif
