#include "Cat.hpp"
Cat::Cat() : Animal()
{
    this->brain = new Brain();
    this->type = "Cat";
    std::cout << "Cat default constructor called" << std::endl;
}
Cat::Cat(const Cat& other) : Animal(other)
{
    type = other.type;
    this->brain = new Brain();
    *(this->brain) = *(other.brain);
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &other)
    {
        Animal::operator=(other);
        type = other.type;
        *(this->brain) = *(other.brain);
    }
    return (*this);
}
Cat::~Cat() 
{
    delete(brain);
    std::cout << "Cat default destructor called" << std::endl;
};
void    Cat::makeSound() const
{
    std::cout << "Meow" << std::endl;
}