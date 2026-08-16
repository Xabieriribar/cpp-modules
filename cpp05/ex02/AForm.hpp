#ifndef AFORM_HPP
#define AFORM_HPP
#include <iostream>
#include <string>
#include <exception>
class Bureaucrat;
class AForm
{
private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;
protected:
    virtual void action() const = 0;
public:
    AForm();
    AForm(const std::string &name, int gradeToSign, int gradeToExecute);
    AForm(const AForm &other);
    AForm &operator=(const AForm &other);
    virtual ~AForm();
    class GradeTooHighException : public std::exception
    { public: virtual const char *what() const throw(); };
    class GradeTooLowException : public std::exception
    { public: virtual const char *what() const throw(); };
    class FormNotSignedException : public std::exception
    { public: virtual const char *what() const throw(); };
    const std::string &getName() const;
    bool getIsSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    void beSigned(const Bureaucrat &bureaucrat);
    void execute(const Bureaucrat &executor) const;
};
std::ostream &operator<<(std::ostream &out, const AForm &form);
#endif
