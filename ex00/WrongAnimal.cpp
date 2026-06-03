#include "WrongAnimal.hpp"
WrongAnimal::WrongAnimal()
{
    type = "";
    std::cout << "WrongAnimal default constructor called" << std::endl;
}
WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
    type = other.type;
    std::cout << "WrongAnimal copy constructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
    std::cout << "WrongAnimal copy assignment operator called" << std::endl;
    if (this != &other)
    {
        type = other.type;
    }
    return (*this);
}
WrongAnimal::~WrongAnimal() 
{
    std::cout << "WrongAnimal default destructor called" << std::endl;
}

void    WrongAnimal::makeSound() const
{
    std::cout << "An animal doesn't bark or meow" << std::endl;
}

const std::string& WrongAnimal::getType() const
{
    return (type);
}