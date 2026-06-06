#ifndef CURE_HPP
#define CURE_HPP

#include "Amateria.hpp"

class Cure: public Amateria
{
  public:
    Cure();
    Cure(const Cure &other);
    operator=(const Cure &other);
    ~Cure();
    AMateria* clone() const;





}
#endif
