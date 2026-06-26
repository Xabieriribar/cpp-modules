#include "AForm.hpp"
#include "Bureaucrat.hpp"

const char* AForm::gradeTooLowException::what() const throw()
{
    return "the grade is too low.";
}

const char* AForm::gradeTooHighException::what() const throw()
{
    return "the grade is too high.";
}

const char *AForm::formNotSignedException::what() const throw()
{
    return "you can't execute a form that isn't signed.";
}

void    AForm::throwException() const
{
        if (_gradeToExecute < 1 || _gradeToSign < 1)
            throw (gradeTooHighException());
        else if (_gradeToExecute > 150 || _gradeToSign > 150)
            throw (gradeTooLowException());
}

AForm::AForm(std::string const formName, int const gradeToSign, int const gradeToExecute) : _formName(formName), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
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

// AForm::AForm(AForm const &other) : _formName(other._formName), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
// {
//     try
//     {
//         throwException();
//     }
//     catch (std::exception & e)
//     {
//         std::cerr << e.what() << "\n";
//     }
// }

// AForm& AForm::operator=(const AForm &other)
// {
//     if (this != &other)
//         _isSigned = other._isSigned;
//     return (*this);
// }

AForm::~AForm() {}

const std::string& AForm::getName() const
{
    return (_formName);
}

int AForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

bool AForm::getAFormState() const
{
    if (_isSigned)
    {
        return (true);
    }
    return (false);

}

std::ostream &operator<<(std::ostream &o, AForm const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is ";
    if (i.getAFormState()) 
        o << "signed.\n";
    else
        o << "unsigned.\n";
    o << "The required grade to sign is : " << i.getGradeToSign() << ".\nThe required grade to execute is : " << i.getGradeToExecute() << ".";
    return (o);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (_gradeToSign < bureaucrat.getGrade())
        return ;
    _isSigned = true;
}

void AForm::execute(Bureaucrat const & executor) const     
{
    try
    {
        if (getAFormState())
            throw (formNotSignedException());
        if (executor.getGrade() > _gradeToSign || executor.getGrade() > _gradeToExecute)
            throw (gradeTooLowException());
        action();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error while executing the form: " <<  e.what() << '\n';
    }
}