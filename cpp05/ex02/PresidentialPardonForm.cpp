#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

const char* PresidentialPardonForm::gradeTooLowException::what() const throw()
{
    return "the grade is too low.";
}

const char* PresidentialPardonForm::gradeTooHighException::what() const throw()
{
    return "the grade is too high.";
}

void    PresidentialPardonForm::throwException() const
{
        if (_gradeToExecute > 137 || _gradeToSign > 145)
            throw (gradeTooLowException());
}

PresidentialPardonForm::PresidentialPardonForm(std::string _target) : AForm("PresidentialPardonForm", 145, 137)
{
    try
    {
        throwException();
        std::ofstream outFile(_target + "_shrubbery");

    }
    catch (std::exception & e)
    {
        std::cerr << "Could not construct form "; 
        std::cerr << e.what() << "\n";
    }
    
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &other) : AForm(other)
{
    try
    {
        throwException();
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {}

const std::string& PresidentialPardonForm::getName() const
{
    return (_formName);
}

int PresidentialPardonForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int PresidentialPardonForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

bool PresidentialPardonForm::getPresidentialPardonFormState() const
{
    if (_isSigned)
    {
        return (true);
    }
    return (false);

}

std::ostream &operator<<(std::ostream &o, PresidentialPardonForm const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is ";
    if (i.getPresidentialPardonFormState()) 
        o << "signed.\n";
    else
        o << "unsigned.\n";
    o << "The required grade to sign is : " << i.getGradeToSign() << ".\nThe required grade to execute is : " << i.getGradeToExecute() << ".";
    return (o);
}

void PresidentialPardonForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (_gradeToSign < bureaucrat.getGrade())
        return ;
    _isSigned = true;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor)
{


}