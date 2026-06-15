#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    ScavTrap scav("Scav");
    FragTrap frag("Frag");

    std::cout << "=== ScavTrap ===" << std::endl;
    scav.attack("target");
    scav.guardGate();

    std::cout << "=== FragTrap ===" << std::endl;
    frag.attack("target");
    frag.highFivesGuys();
    return (0);
}
