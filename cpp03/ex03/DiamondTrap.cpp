#include "DiamondTrap.hpp"


DiamondTrap::DiamondTrap() : ClapTrap(), FragTrap(), ScavTrap() 
{
    this->HitPoints = FragTrap::HitPoints;
    this->EnergyPoints = ScavTrap::EnergyPoints;
    this->AttackDamage = FragTrap::AttackDamage;
    std::cout << "DiamondTrap default constructor called" << std::endl;
}
DiamondTrap::DiamondTrap(std::string Name) : ClapTrap(Name + "_clap_name"), FragTrap(Name), ScavTrap(Name) 
{
    name = Name;
    this->HitPoints = FragTrap::HitPoints;
    this->EnergyPoints = ScavTrap::EnergyPoints;
    this->AttackDamage = FragTrap::AttackDamage;
    std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) : ClapTrap(other), FragTrap(other), ScavTrap(other)
{
    this->name = other.name;
    this->HitPoints = other.HitPoints;
    this->EnergyPoints = other.EnergyPoints;
    this->AttackDamage = other.AttackDamage;
    std::cout << "DiamondTrap copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &other)
{
    std::cout << "DiamondTrap copy assignment operator called" << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other);
        this->HitPoints = other.HitPoints;
        this->EnergyPoints = other.EnergyPoints;
        this->AttackDamage = other.AttackDamage;
        this->name = other.name;
    }
    return (*this);
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap default destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
    std::cout << "Hey guys, my name is " << name << " and my ClapTrap name is " << ClapTrap::name << "!" << std::endl;
}