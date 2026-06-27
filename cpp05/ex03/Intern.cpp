#include "Intern.hpp"

Intern::Intern() {}
Intern(Intern const & other);
Intern& operator=(Intern const & other);
~Intern();

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