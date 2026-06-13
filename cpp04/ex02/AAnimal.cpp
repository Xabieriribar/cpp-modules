#include "AAnimal.hpp"
AAnimal::AAnimal()
{
    type = "";
    std::cout << "AAnimal default constructor called" << std::endl;
}
AAnimal::AAnimal(const AAnimal& other)
{
    type = other.type;
    std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
    std::cout << "AAnimal copy assignment operator called" << std::endl;
    if (this != &other)
    {
        type = other.type;
    }
    return (*this);
}
AAnimal::~AAnimal() 
{
    std::cout << "AAnimal default destructor called" << std::endl;
}

void    AAnimal::makeSound() const
{
    std::cout << "An animal doesn't bark or meow" << std::endl;
}

const std::string& AAnimal::getType() const
{
    return (type);
}
