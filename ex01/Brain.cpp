#include "Brain.hpp"
Brain::Brain()
{
    int i = 0;
    while (i < 100)
        ideas[i++] = "Empty string";
    std::cout << "Brain default constructor called" << std::endl;
}
Brain::Brain(const Brain& other)
{
    std::cout << "Brain copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
    std::cout << "Brain copy assignment operator called" << std::endl;
    if (this != &other)
    {
    }
    return (*this);
}
Brain::~Brain() 
{
    std::cout << "Brain default destructor called" << std::endl;
};
void    Brain::makeSound() const
{
    std::cout << "Meow" << std::endl;
}