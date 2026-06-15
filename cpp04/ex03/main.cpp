#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    MateriaSource source;
    Character bob("bob");
    Character me("me");

    std::cout << "=== source and use ===" << std::endl;
    source.learnMateria(new Ice());
    source.learnMateria(new Cure());
    me.equip(source.createMateria("ice"));
    me.equip(source.createMateria("cure"));
    me.use(0, bob);
    me.use(1, bob);

    std::cout << "=== bounds and unknown type ===" << std::endl;
    me.use(-1, bob);
    me.use(4, bob);
    delete source.createMateria("unknown");

    std::cout << "=== deep copy ===" << std::endl;
    Character copy(me);
    copy.use(0, bob);
    copy = copy;

    return (0);
}
