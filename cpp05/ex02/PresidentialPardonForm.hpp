#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class PresidentialPardonForm : public AForm
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        PresidentialPardonForm(std::string _target);
        PresidentialPardonForm(PresidentialPardonForm const &other);
        PresidentialPardonForm& operator=(const PresidentialPardonForm &other);
        ~PresidentialPardonForm();
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
        bool getPresidentialPardonFormState() const;
        void beSigned(const Bureaucrat &bureaucrat);
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void    throwException() const;
        void execute(Bureaucrat const & executor);
};
#endif