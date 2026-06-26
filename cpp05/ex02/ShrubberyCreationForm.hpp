
#ifndef FORM_HPP
#define FORM_HPP

#include "AForm.hpp"

class Bureaucrat;

class ShrubberyCreationForm : public AForm 
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        ShrubberyCreationForm(std::string _target);
        ShrubberyCreationForm(ShrubberyCreationForm const &other);
        ShrubberyCreationForm& operator=(const ShrubberyCreationForm &other);
        ~ShrubberyCreationForm();
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
        bool getShrubberyCreationFormState() const;
        void beSigned(const Bureaucrat &bureaucrat);
        int getGradeToSign() const;
        int getGradeToExecute() const;
        void    throwException() const;
        void execute(Bureaucrat const & executor);
};

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm const &i);

#endif
