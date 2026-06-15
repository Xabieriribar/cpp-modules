#include "ScavTrap.hpp"

int main(void)
{
    ScavTrap scav("Serena");

    std::cout << "=== inherited and overridden actions ===" << std::endl;
    scav.attack("target");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();

    std::cout << "=== copy ===" << std::endl;
    ScavTrap copy(scav);
    copy.attack("another target");
    return (0);
}
