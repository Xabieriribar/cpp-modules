#include "Intern.hpp"

Intern::Intern() {}
Intern(Intern const & other)
Intern& operator=(Intern const & other);
~Intern();


const char* Intern::wrongFormNameException::what() const throw()
{
    return "The form's name is incorrect.";
}
AForm* Intern::makeForm(std::string _formName, std::string _target)
{
    try
    {


    }
    except(std::exception & e)
    {
        std::err << e.what() << std::endl;
    }
}