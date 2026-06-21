
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Bureaucrat
{
    private:
        std::string const _name;
        int         _grade;
    public:
        Bureaucrat(std::string const name, int grade);
        Bureaucrat(Bureaucrat const &other);
        Bureaucrat& operator=(const Bureaucrat &other);
        ~Bureaucrat();
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
        int getGrade() const;
        void signForm(Form const &frm);
        void increment();
        void decrement();
};

std::ostream &operator<<(std::ostream &o, Bureaucrat const &i);

#endif