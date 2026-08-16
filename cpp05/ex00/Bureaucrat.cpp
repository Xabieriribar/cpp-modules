#include "Bureaucrat.hpp"

void    Bureaucrat::throwException() const
{
        if (_grade < 1)
            throw (GradeTooHighException());
        else if (_grade > 150)
            throw (GradeTooLowException());
}

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade) 
{
    throwException();
}

Bureaucrat::Bureaucrat(Bureaucrat const &other) : _name(other._name), _grade(other._grade) 
{
    throwException();
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
    if (_grade - 1 <= 0)
        throw (GradeTooHighException());
    _grade -= 1;
}

void Bureaucrat::decrement()
{
    if (_grade + 1 > 150)
        throw (GradeTooLowException());
    _grade += 1;
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
    o << i.getName() << "," << " bureaucrat grade " << i.getGrade() << ".";
    return (o);
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade too low. The grade of a bureaucrat should be inferior or equal to 150";
}
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade too high. The grade of a bureaucrat should be superior to 0";
}