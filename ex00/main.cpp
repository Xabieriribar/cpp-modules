#include "Zombie.hpp"

int main(void)
{
    randomChump("Foo1");
    Zombie *zombie = newZombie("Foo2");
    zombie->announce();
    delete(zombie);
}