
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
    Character original("original");
    original.equip(src->createMateria("ice"));

    Character copy(original);

    original.unequip(0);
    copy.use(0, *bob);
    delete bob;
    delete src;
    return 0;
}
