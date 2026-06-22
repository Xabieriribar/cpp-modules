#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "PresidentialPardonForm.hpp"

class PresidentialPardonForm : public PresidentialPardonForm
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        PresidentialPardonForm(std::string const formName, int const gradeToSign, int const gradeToExecute);
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