#include "Cure.hpp"

Cure::Cure() : AMateria("Cure") {}

Cure::Cure(const Cure &other) : AMateria(other._type) {}

Cure& Cure::operator=(const Cure &other)
{
    if (this != &other)
    {
        _type = other._type;
        AMateria::operator=(other);
    }
    return (*this);
}

Cure::~Cure() {}

AMateria* Cure::clone() const
{
    AMateria *object = new Cure();

    return (object);
}