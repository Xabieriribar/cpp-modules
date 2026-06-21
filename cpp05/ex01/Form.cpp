#include "Form.hpp"

Form::Form(std::string const formName, int const gradeToSign, int const gradeToExecute) : _formName(formName), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) 
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

Form::Form(Form const &other) : _formName(other._formName), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) 
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

bool Form::getFormState(bool printState) const
{
    if (_isSigned)
    {
        if (printState)
            std::cout << "signed";
        return (true);
    }
    if (printState)
        std::cout << "unsigned";
    return (false);

}

std::ostream &operator<<(std::ostream &o, Form const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is " << i.getFormState(true) << ".\nThe required grade to sign it is : " << i.getGradeToSign() << ".\nThe required grade to execute is is : " << i.getGradeToExecute() << ".";
    return (o);
}

const char* Form::gradeTooLowException::what() const throw()
{
    return "The grade required to sign this form is superior than the grade of the bureaucrat";
}
const char* Form::gradeTooHighException::what() const throw()
{
    return "The grade required to sign this form is superior than the grade of the bureaucrat";
}

void Form::beSigned(Bureaucrat const &bureaucrat) const
{
    try
    {
        if (_gradeToSign < bureaucrat.getGrade())
            throw (gradeTooLowException());
        _isSigned = true;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << '\n';
    }
}