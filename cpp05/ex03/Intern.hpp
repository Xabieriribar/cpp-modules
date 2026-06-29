#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"

class Bureaucrat;

class Intern  
{
    private:
        AForm* presidentialPardonForm(const std::string& formTarget);
        AForm* robotomyRequestForm (const std::string& formTarget);
        // AForm* shrubberyCreationForm(const std::string& formTarget);
        std::string _forms[3];
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
};

#endif
