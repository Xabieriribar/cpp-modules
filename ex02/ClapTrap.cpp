#include "ClapTrap.hpp"


ClapTrap::ClapTrap(std::string Name) : name(Name), HitPoints(10), EnergyPoints(10), AttackDamage(0) 
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) : name(other.name), HitPoints(other.HitPoints), EnergyPoints(other.EnergyPoints), AttackDamage(other.AttackDamage) 
{
    std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << "ClapTrap copy assignment operator called" << std::endl;
    if (this != &other)
    {
        this->name = other.name;
        this->HitPoints = other.HitPoints;
        this->EnergyPoints = other.EnergyPoints;
        this->AttackDamage = other.AttackDamage;
    }
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap default destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->EnergyPoints > 0 && this->HitPoints > 0)
    {
        this->EnergyPoints -= 1;
        std::cout << "Clap Trap " << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
    }
    else
        std::cout << "Clap Trap doesn't have enough power to attack." << std::endl;
    std::cout << "Clap Trap " << this->name << " has now " << this->EnergyPoints <<  " energy points." << std::endl;
    
}
void ClapTrap::takeDamage(unsigned int amount)
{
    this->HitPoints -= amount;
    std::cout << "Clap Trap " << this->name << " has taken damage. Its Hit points are now " << this->HitPoints << std::endl;
}
void ClapTrap::beRepaired(unsigned int amount)
{
    this->HitPoints += amount;
    std::cout << "Clap Trap " << this->name << " is being repared by " << this->HitPoints << " points." << std::endl;
}