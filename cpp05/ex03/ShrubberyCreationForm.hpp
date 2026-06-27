
#ifndef FORM_HPP
#define FORM_HPP

#include "AForm.hpp"

class Bureaucrat;

class ShrubberyCreationForm : public AForm 
{
    private:
        std::string _target;
    public:
        ShrubberyCreationForm(std::string Target);
        ShrubberyCreationForm(ShrubberyCreationForm const &other);
        ShrubberyCreationForm& operator=(const ShrubberyCreationForm &other);
        ~ShrubberyCreationForm();
        void action() const;
};

#endif
