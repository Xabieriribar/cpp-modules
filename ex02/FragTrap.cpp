#include "FragTrap.hpp"


FragTrap::FragTrap(std::string Name) : ClapTrap(Name)
{
    this->HitPoints = 100;
    this->EnergyPoints = 100;
    this->AttackDamage = 30;
    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
    this->HitPoints = 100;
    this->EnergyPoints = 100;
    this->AttackDamage = 30;
    std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &other)
{
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other);
        this->HitPoints = 100;
        this->EnergyPoints = 100;
        this->AttackDamage = 30;
    }
    return (*this);
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap default destructor called" << std::endl;
}

void FragTrap::attack(const std::string& target)
{
    if (this->EnergyPoints > 0 && this->HitPoints > 0)
    {
        this->EnergyPoints -= 1;
        std::cout << "Frag Trap " << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
    }
    else
        std::cout << "Frag Trap doesn't have enough power to attack." << std::endl;
    std::cout << "Frag Trap " << this->name << " has now " << this->EnergyPoints <<  " energy points." << std::endl;
    
}

void FragTrap::highFiveGuys()
{
    std::cout << "Hey guys, FragTrap here, high five!" << std::endl;
}