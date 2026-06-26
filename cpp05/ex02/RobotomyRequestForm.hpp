
#ifndef FORM_HPP
#define FORM_HPP

#include "AForm.hpp"
#include <stdlib.h>

class Bureaucrat;

class RobotomyRequestForm : public AForm
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        RobotomyRequestForm(std::string _target);
        RobotomyRequestForm(RobotomyRequestForm const &other);
        RobotomyRequestForm& operator=(const RobotomyRequestForm &other);
        ~RobotomyRequestForm();
        class gradeTooLowException : public std::exception
        {
            public:
                const char* what() const throw();
        };
        class gradeTooHighException : public std::exception
        {
            public:
                const char* what() const throw();
        };
        const std::string& getName() const;
        bool getRobotomyRequestFormState() const;
        void beSigned(const Bureaucrat &bureaucrat);
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void    throwException() const;
        void execute(Bureaucrat const & executor);
        void robotomize();
};

std::ostream &operator<<(std::ostream &o, RobotomyRequestForm const &i);

#endif
\