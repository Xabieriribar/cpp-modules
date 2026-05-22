#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    int index;

    index = 0;
    Zombie *zombieHorde = new Zombie[N];
    Zombie *ourZombie;
    while (index < N)
    {
        ourZombie = randomChump(name);
        zombieHorde[index] = ourZombie;
        index++;
    }
    return (zombieHorde);
}