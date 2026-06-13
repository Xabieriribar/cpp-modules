#include "Zombie.hpp"

void    Zombie::setName(std::string name)
{
    zombieName = name;
}

Zombie* zombieHorde(int N, std::string name)
{
    int index;

    index = 0;
    Zombie *zombieHorde = new Zombie[N];
    while (index < N)
    {
        zombieHorde[index].setName(name);
        index++;
    }
    return (zombieHorde);
}