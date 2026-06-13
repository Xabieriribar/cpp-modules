#include "ScavTrap.hpp"

int main(void)
{
    ScavTrap d("Scabitrabi");
    ScavTrap e("Xabi");
    int     DefaultPoints = 100;
    int     DefaultEnergyPoints = 50;
    int     DefaultAttackDamage = 20;
    int     TestIndex = 0;

    while (TestIndex < DefaultEnergyPoints + 1 && DefaultPoints - DefaultAttackDamage > 0)
    {
        d.attack("e");
        if (TestIndex != DefaultEnergyPoints)
            e.takeDamage(DefaultAttackDamage);
        DefaultPoints -= DefaultAttackDamage;
        TestIndex++;
    }
    d.guardGate();
    return 0;
}