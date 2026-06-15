#include "Zombie.hpp"

int main(void)
{
    std::cout << "=== stack zombie ===" << std::endl;
    randomChump("Stack");

    std::cout << "=== heap zombie ===" << std::endl;
    Zombie *zombie = newZombie("Heap");
    zombie->announce();
    delete zombie;
    return (0);
}
