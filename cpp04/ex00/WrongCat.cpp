#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal()
{
    this->type = "WrongCat";
    std::cout << "WrongCat default constructor called" << std::endl;
}
WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
    type = other.type;
    std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
    std::cout << "WrongCat copy assignment operator called" << std::endl;
    if (this != &other)
    {
        WrongAnimal::operator=(other);
        type = other.type;
    }
    return (*this);
}

WrongCat::~WrongCat() 
{
    std::cout << "WrongCat default destructor called" << std::endl;
};

void    WrongCat::makeSound() const
{
    std::cout << "It is not going to make Meow" << std::endl;
}