#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>

class Zombie
{
    private:
        std::string zombieName;
    public:
        Zombie();
        Zombie(std::string name);
        ~Zombie();
        
        void setName(std::string name);
        void announce(void);
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);
Zombie* zombieHorde(int N, std::string name);

#endif