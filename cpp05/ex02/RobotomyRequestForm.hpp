
#ifndef FORM_HPP
#define FORM_HPP

#include "AForm.hpp"
#include <stdlib.h>
#include <ctime>

class Bureaucrat;

class RobotomyRequestForm : public AForm
{
    private:
        std::string _target;
    public:
        RobotomyRequestForm(std::string Target);
        RobotomyRequestForm(RobotomyRequestForm const &other);
        RobotomyRequestForm& operator=(const RobotomyRequestForm &other);
        ~RobotomyRequestForm();
        void action() const;
};

#endif