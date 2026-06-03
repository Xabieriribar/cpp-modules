#include "Dog.hpp"
Dog::Dog() : Animal()
{
    this->brain = new Brain();
    type = "Dog";
    std::cout << "Dog default constructor called" << std::endl;
}
Dog::Dog(const Dog& other) : Animal(other)
{
    this->brain = new Brain();
    type = other.type;
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &other)
    {
        Animal::operator=(other);
        type = other.type;
        *(this->brain) = *(other.brain);
    }
    return (*this);
}
Dog::~Dog() 
{
    delete(brain);
    std::cout << "Dog default destructor called" << std::endl;
};

void    Dog::makeSound() const
{
    std::cout << "Bark" << std::endl;
}