#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
    private:
        AMateria* _templates[4];
    public:
        MateriaSource();
        MateriaSource(const IMateriaSource &other);
        MateriaSource &operator=(const MateriaSource &other);
        virtual ~MateriaSource() {}
        virtual void learnMateria(AMateria*) = 0;
        virtual AMateria* createMateria(std::string const & type) = 0;
};

#endif
