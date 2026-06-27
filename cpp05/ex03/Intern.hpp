#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include "AForm.hpp"

class Bureaucrat;

class Intern  
{
    public:
        Intern();
        Intern(Intern const & other);
        Intern& operator=(Intern const & other);
        ~Intern();
        class wrongFormNameException : public std::exception
        {
            public:
                const char* what() const throw();
        };
        AForm* makeForm(std::string _formName, std::string _target);
}

#endif
