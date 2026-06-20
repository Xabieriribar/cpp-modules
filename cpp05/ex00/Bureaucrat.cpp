#include "Bureaucrat.hpp"
Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade) 
{
    try 
    {
        if (_grade < 1 || _grade > 150)
            throw; 
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << '\n';
    }


}

Bureaucrat::Bureaucrat(Bureaucrat const &other) : _name(other._name), _grade(other._grade) 
{
    try 
    {
        if (_grade < 1 || _grade > 150)
            throw;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << '\n';
    }
}
Bureaucrat& Bureaucrat::operator=(const Bureaucrat &other)
{
    if (this != &other)
        _grade = other._grade;
    return (*this);
}

Bureaucrat::~Bureaucrat() {}

void Bureaucrat::increment()
{
    try
    {
        if (_grade < 1 || _grade > 150)
            throw;
        _grade += 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void Bureaucrat::decrement()
{
    try
    {
        if (_grade < 1 || _grade > 150)
            throw;
        _grade -= 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const std::string& Bureaucrat::getName() const
{
    return (_name);
}

int Bureaucrat::getGrade() const
{
    return (_grade);
}

std::ostream &operator<<(std::ostream &o, Bureaucrat const &i)
{
    o << i.getName() << "," << " bureaucrat grade " << i.getGrade() << "." << std::endl;
    return (o);
}