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
    int i = 0;
    while (i < 100)
    {
        this->ideas[i] = other.ideas[i];
        i++;
    }
    std::cout << "Brain copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
    std::cout << "Brain copy assignment operator called" << std::endl;
    if (this != &other)
    {
        int i = 0;
        while (i < 100)
        {
            this->ideas[i] = other.ideas[i];
            i++;
        }
    }
    return (*this);
}
Brain::~Brain() 
{
    std::cout << "Brain default destructor called" << std::endl;
};