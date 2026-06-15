#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap robot("CL4P");

    std::cout << "=== normal actions ===" << std::endl;
    robot.attack("target");
    robot.takeDamage(4);
    robot.beRepaired(2);

    std::cout << "=== lethal damage ===" << std::endl;
    robot.takeDamage(100);
    robot.attack("target");
    robot.beRepaired(2);
    return (0);
}
