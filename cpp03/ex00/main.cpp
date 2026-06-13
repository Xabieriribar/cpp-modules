#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap a("Bartolomeo");
    ClapTrap b(a);
    ClapTrap c("Manolin");
    int     DefaultPoints = 10;
    int     DefaultEnergyPoints = 100;
    int     RepairValue = 1;
    int     DefaultAttackDamage = 1;
    int     TestIndex = 0;

    c = b;
    while (TestIndex < DefaultEnergyPoints + 1)
    {
        a.attack("b");
        if (TestIndex != DefaultEnergyPoints)
            b.takeDamage(DefaultAttackDamage);
        TestIndex++;
    }
    a.beRepaired(RepairValue);
    return 0;
}