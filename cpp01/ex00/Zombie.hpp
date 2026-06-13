#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>

class Zombie
{
    private:
        std::string zombieName;
    public:
        Zombie(std::string name);
        ~Zombie();
        
        void announce(void);
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif