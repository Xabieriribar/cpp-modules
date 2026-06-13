#include "FragTrap.hpp"

int main(void)
{
    FragTrap d("Scabitrabi");
    FragTrap e("Xabi");
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
    d.highFiveGuys();
    return 0;
}