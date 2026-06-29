#include "Intern.hpp"

Intern::Intern() 
{
    _forms[0] = "robotomy request";
    _forms[1] = "shrubbery creation";
    _forms[2] = "presidential pardon";
}

Intern::Intern(Intern const & other)
{
    int i = 0;
    while (i < 3)
    {
        _forms[i] = other._forms[i];
        i++;
    }
}

Intern& Intern::operator=(Intern const & other)
{
    if (this != &other)
    {
        int i = 0;
        while (i < 3)
        {
            _forms[i] = other._forms[i];
            i++;
        }
    }
    return (*this);

}
Intern::~Intern() {}


const char* Intern::wrongFormNameException::what() const throw()
{
    return "The form's name is incorrect.";
}

AForm* Intern::presidentialPardonForm (const std::string& formTarget)
{
    AForm* president = new PresidentialPardonForm(formTarget);
    return (president);
}
AForm* Intern::robotomyRequestForm(const std::string& formTarget)
{
    AForm* robotomy = new RobotomyRequestForm(formTarget);
    return (robotomy);
}

AForm* Intern::shrubberyCreationForm(const std::string& formTarget)
{
    AForm* robotomy = new ShrubberyCreationForm(formTarget);
    return (robotomy);
}
AForm* Intern::makeForm(std::string _formName, std::string _target)
{
    AForm* (Intern::*pointer_array[3])(const std::string& formTarget);
    pointer_array[0] = &Intern::robotomyRequestForm;
    pointer_array[1] = &Intern::shrubberyCreationForm;
    pointer_array[2] = &Intern::presidentialPardonForm;
    try
    {
        int i = 0;
        while (i < 3 && _formName != _forms[i])
            i++;
        if (i > 2)
            throw (wrongFormNameException());
        return (this->*pointer_array[i])(_target);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (NULL);
}