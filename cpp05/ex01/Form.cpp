#include "Form.hpp"
#include "Bureaucrat.hpp"

const char* Form::gradeTooLowException::what() const throw()
{
    return "the grade is too low.";
}

const char* Form::gradeTooHighException::what() const throw()
{
    return "the grade is too high.";
}

void    Form::throwException() const
{
        if (_gradeToExecute < 1 || _gradeToSign < 1)
            throw (gradeTooHighException());
        else if (_gradeToExecute > 150 || _gradeToSign > 150)
            throw (gradeTooLowException());
}

Form::Form(std::string const formName, int const gradeToSign, int const gradeToExecute) : _formName(formName), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
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

Form::Form(Form const &other) : _formName(other._formName), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
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

Form& Form::operator=(const Form &other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

Form::~Form() {}

const std::string& Form::getName() const
{
    return (_formName);
}

int Form::getGradeToSign() const
{
    return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
    return (_gradeToExecute);
}

bool Form::getFormState() const
{
    if (_isSigned)
    {
        return (true);
    }
    return (false);

}

std::ostream &operator<<(std::ostream &o, Form const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is ";
    if (i.getFormState()) 
        o << "signed.\n";
    else
        o << "unsigned.\n";
    o << "The required grade to sign is : " << i.getGradeToSign() << ".\nThe required grade to execute is : " << i.getGradeToExecute() << ".";
    return (o);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (_gradeToSign < bureaucrat.getGrade())
        return ;
    _isSigned = true;
}
