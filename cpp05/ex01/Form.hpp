
#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Form  
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        Form(std::string const formName, int const gradeToSign, int const gradeToExecute);
        Form(Form const &other);
        Form& operator=(const Form &other);
        ~Form();
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
        void throwException() const;
        void getReason() const;
        bool getFormState(bool printState) const;
        void beSigned(Bureaucrat const &bureaucrat) const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
};

std::ostream &operator<<(std::ostream &o, Form const &i);

#endif
