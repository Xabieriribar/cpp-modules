#include "Zombie.hpp"

void Zombie::announce(void)
{
    std::cout << zombieName << ":BraiiiiiiinnnzzzZ...." << std::endl;
}

Zombie::Zombie(std::string name)
{
    zombieName = name;
}

Zombie::~Zombie()
{
    std::cout << zombieName << " was destroyed" << std::endl;
}
