#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

const char* RobotomyRequestForm::gradeTooLowException::what() const throw()
{
    return "the grade is too low.";
}

const char* RobotomyRequestForm::gradeTooHighException::what() const throw()
{
    return "the grade is too high.";
}

void    RobotomyRequestForm::throwException() const
{
        if (_gradeToExecute > 45 || _gradeToSign > 72)
            throw (gradeTooLowException());
}


void RobotomyRequestForm::robotomize()
{
    int randomValue = rand() % 100 + 1;
    if (randomValue <= 50)
        std::cout << _target << "has been robotomized" << std::endl;
    else
        std::cout << _target << "has been robotomized" << std::endl;
}


RobotomyRequestForm::RobotomyRequestForm(std::string _target) : AForm("RobotomyRequestForm", 72, 45)
{
    try
    {
        throwException();
        robotomize();
    }
    catch (std::exception & e)
    {
        std::cerr << "Could not construct form "; 
        std::cerr << e.what() << "\n";
    }
    
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other) : AForm(other)
{
    try
    {
        throwException();
        int randomValue = rand() % 100 + 1;
        if (randomValue <= 50)
            std::cout << _target << "has been robotomized" << std::endl;
        else
            std::cout << "Robotomy failed for " << _target << std::endl;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {}

const std::string& RobotomyRequestForm::getName() const
{
    return (_formName);
}

int RobotomyRequestForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int RobotomyRequestForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

bool RobotomyRequestForm::getRobotomyRequestFormState() const
{
    if (_isSigned)
    {
        return (true);
    }
    return (false);

}

std::ostream &operator<<(std::ostream &o, RobotomyRequestForm const &i)
{
    o << "The forms name is : " << i.getName() << ".\n" << "Currently this form is ";
    if (i.getRobotomyRequestFormState()) 
        o << "signed.\n";
    else
        o << "unsigned.\n";
    o << "The required grade to sign is : " << i.getGradeToSign() << ".\nThe required grade to execute is : " << i.getGradeToExecute() << ".";
    return (o);
}

void RobotomyRequestForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (_gradeToSign < bureaucrat.getGrade())
        return ;
    _isSigned = true;
}
