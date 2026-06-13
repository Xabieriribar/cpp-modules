
#include "IMateriaSource.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* bob = new Character("bob");
    ICharacter* me = new Character("me");
    me->equip(src->createMateria("ice"));  // slot 0
    me->equip(src->createMateria("cure")); // slot 1
    me->equip(src->createMateria("ice"));  // slot 2
    me->equip(src->createMateria("cure")); // slot 3
    me->equip(src->createMateria("ice"));  // should do nothing safely
    delete bob;
    delete src;
    return 0;
}
