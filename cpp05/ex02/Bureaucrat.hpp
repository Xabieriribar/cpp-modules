#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
#include <iostream>
#include <string>
#include <exception>
class AForm;
class Bureaucrat
{
private:
    const std::string _name;
    int _grade;
public:
    Bureaucrat();
    Bureaucrat(const std::string &name, int grade);
    Bureaucrat(const Bureaucrat &other);
    Bureaucrat &operator=(const Bureaucrat &other);
    ~Bureaucrat();
    class GradeTooHighException : public std::exception
    { public: virtual const char *what() const throw(); };
    class GradeTooLowException : public std::exception
    { public: virtual const char *what() const throw(); };
    const std::string &getName() const;
    int getGrade() const;
    void increment();
    void decrement();
    void signForm(AForm &form) const;
    void executeForm(const AForm &form) const;
};
std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);
#endif
