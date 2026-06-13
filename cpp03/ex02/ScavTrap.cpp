#include "ScavTrap.hpp"


ScavTrap::ScavTrap() : ClapTrap()
{
    this->HitPoints = 100;
    this->EnergyPoints = 50;
    this->AttackDamage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}
ScavTrap::ScavTrap(std::string Name) : ClapTrap(Name)
{
    this->HitPoints = 100;
    this->EnergyPoints = 50;
    this->AttackDamage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
    this->HitPoints = other.HitPoints;
    this->EnergyPoints = other.EnergyPoints;
    this->AttackDamage = other.AttackDamage;
    std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &other)
{
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other);
        this->HitPoints = other.HitPoints;
        this->EnergyPoints = other.EnergyPoints;
        this->AttackDamage = other.AttackDamage;
    }
    return (*this);
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap default destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (this->EnergyPoints > 0 && this->HitPoints > 0)
    {
        this->EnergyPoints -= 1;
        std::cout << "Scav Trap " << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
    }
    else
        std::cout << "Scav Trap doesn't have enough power to attack." << std::endl;
    std::cout << "Scav Trap " << this->name << " has now " << this->EnergyPoints <<  " energy points." << std::endl;
    
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap is in Gate keeper mode" << std::endl;
}