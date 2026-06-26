
#ifndef FORM_HPP
#define FORM_HPP

#include "AForm.hpp"
#include <stdlib.h>

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
        void action();
};

std::ostream &operator<<(std::ostream &o, RobotomyRequestForm const &i);

#endif
\