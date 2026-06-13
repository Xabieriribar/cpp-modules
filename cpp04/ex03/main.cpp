#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");
    Character me("me");

    me.equip(new Ice());
    me.equip(new Cure());

    me = me;

    me.use(0, bob);
    me.use(1, bob);

    return 0;
}