#include "Zombie.hpp"

int main(void)
{
    int numberOfZombies;
    int index;
    Zombie *horde;

    numberOfZombies = 10;
    horde = zombieHorde(numberOfZombies, "Xabi");
    index = 0;
    while (index < numberOfZombies)
    {
        horde[index].announce();
        index++;
    }
    delete[] horde;
    return 0;

}