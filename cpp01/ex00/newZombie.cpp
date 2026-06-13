#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
    Zombie *ourZombie;

    ourZombie = new Zombie(name);
    return (ourZombie);
}