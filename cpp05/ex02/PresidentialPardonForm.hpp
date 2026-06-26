#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class PresidentialPardonForm : public AForm
{
    private:
        std::string _target;
    public:
        PresidentialPardonForm(std::string Target);
        PresidentialPardonForm(PresidentialPardonForm const &other);
        PresidentialPardonForm& operator=(const PresidentialPardonForm &other);
        ~PresidentialPardonForm();
        void action();
};
#endif