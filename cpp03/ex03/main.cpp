#include "DiamondTrap.hpp"

int main(void)
{
    DiamondTrap diamond("Diamond");

    std::cout << "=== diamond identity ===" << std::endl;
    diamond.whoAmI();
    std::cout << "=== inherited abilities ===" << std::endl;
    diamond.attack("target");
    diamond.guardGate();
    diamond.highFivesGuys();

    std::cout << "=== copy ===" << std::endl;
    DiamondTrap copy(diamond);
    copy.whoAmI();
    return (0);
}
