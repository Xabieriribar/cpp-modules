#include "ShrubberyCreationForm.hpp"
<<<<<<< HEAD

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
        if (_gradeToExecute < 1 || _gradeToSign < 1)
            throw (gradeTooHighException());
        else if (_gradeToExecute > 150 || _gradeToSign > 150)
            throw (gradeTooLowException());
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const formName, int const gradeToSign, int const gradeToExecute) : _formName(formName), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
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

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : _formName(other._formName), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
=======
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string Target) : AForm("ShrubberyCreationForm", 145, 137), _target(Target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : AForm(other)
>>>>>>> f1e81bbb7c1301455035828b7bc3a53601f92ede
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
<<<<<<< HEAD
        _isSigned = other._isSigned;
=======
    {
        operator=(other);
        _target = other._target;
    }
>>>>>>> f1e81bbb7c1301455035828b7bc3a53601f92ede
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

<<<<<<< HEAD
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
=======
void    ShrubberyCreationForm::action() const
{
    std::cout << _target << " target has been pardoned Zaphod Beeblebrox." << std::endl;
}
>>>>>>> f1e81bbb7c1301455035828b7bc3a53601f92ede
