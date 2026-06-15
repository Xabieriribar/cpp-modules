#include "Zombie.hpp"

int main(void)
{
    int numberOfZombies;
    int index;
    Zombie *horde;

    numberOfZombies = 5;
    horde = zombieHorde(numberOfZombies, "Horde");
    index = 0;
    while (index < numberOfZombies)
    {
        horde[index].announce();
        index++;
    }
    delete [] horde;
    return (0);
}
