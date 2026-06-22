#include "Bureaucrat.hpp"

void    Bureaucrat::throwException() const
{
        if (_grade < 1)
            throw (gradeTooHighException());
        else if (_grade > 150)
            throw (gradeTooLowException());
}

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade) 
{
    try 
    {
        throwException();
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
        throwException();
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
        if (_grade - 1 <= 0)
            throw (gradeTooHighException());
        _grade -= 1;
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
        if (_grade + 1 > 150)
            throw (gradeTooLowException());
        _grade += 1;
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
    o << i.getName() << "," << " bureaucrat grade " << i.getGrade() << ".";
    return (o);
}

const char* Bureaucrat::gradeTooLowException::what() const throw()
{
    return "Grade too low. The grade of a bureaucrat should be inferior or equal to 150.";
}
const char* Bureaucrat::gradeTooHighException::what() const throw()
{
    return "Grade too high. The grade of a bureaucrat should be superior to 0.";
}

void Bureaucrat::signForm(Form &frm)
{
    frm.beSigned(*this);
    try
    {
        if (frm.getFormState())
            std::cout << _name << " signed " << frm.getName() << std::endl;
        else
            throw Form::gradeTooLowException();
    }
    catch (std::exception & e)
    {
            std::cout << _name << " couldn't sign " << frm.getName() << " because " << e.what() << std::endl;
    }

}