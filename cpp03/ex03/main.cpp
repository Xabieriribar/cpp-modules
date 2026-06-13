#include "DiamondTrap.hpp"

int main(void)
{
    DiamondTrap d("Scabitrabi");
    DiamondTrap e("Xabi");
    int     DefaultPoints = 100;
    int     DefaultEnergyPoints = 100;
    int     DefaultAttackDamage = 30;
    int     TestIndex = 0;

    while (TestIndex < DefaultEnergyPoints + 1 && DefaultPoints - DefaultAttackDamage > 0)
    {
        d.attack("e");
        if (TestIndex != DefaultEnergyPoints && DefaultPoints > 0)
            e.takeDamage(DefaultAttackDamage);
        DefaultPoints -= DefaultAttackDamage;
        TestIndex++;
    }
    d.whoAmI();
    return 0;
}