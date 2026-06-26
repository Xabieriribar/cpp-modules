#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

const char* ShrubberyCreationForm::gradeTooLowException::what() const throw()
{
    return "the grade is too low.";
}

const char* ShrubberyCreationForm::gradeTooHighException::what() const throw()
{
    return "the grade is too high.";
}

void    ShrubberyCreationForm::throwException() const
{
        if (_gradeToExecute > 5 || _gradeToSign > 25)
            throw (gradeTooLowException());
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string _type) : AForm("ShrubberyCreationForm", 25, 5)
{
    try
    {
        throwException();
    }
    catch (std::exception & e)
    {
        std::cerr << "Could not construct form "; 
        std::cerr << e.what() << "\n";
    }
    
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : AForm(other)
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

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

const std::string& ShrubberyCreationForm::getName() const
{
    return (_formName);
}

int ShrubberyCreationForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int ShrubberyCreationForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

bool ShrubberyCreationForm::getShrubberyCreationFormState() const
{
    if (_isSigned)
    {
        return (true);
    }
    return (false);

}

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is ";
    if (i.getShrubberyCreationFormState()) 
        o << "signed.\n";
    else
        o << "unsigned.\n";
    o << "The required grade to sign is : " << i.getGradeToSign() << ".\nThe required grade to execute is : " << i.getGradeToExecute() << ".";
    return (o);
}

void ShrubberyCreationForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (_gradeToSign < bureaucrat.getGrade())
        return ;
    _isSigned = true;
}
