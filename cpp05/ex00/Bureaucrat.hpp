
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

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
        const std::string& getName() const;
        int getGrade() const;
        void increment();
        void decrement();
};

std::ostream &operator<<(std::ostream &o, Bureaucrat const &i);

#endif