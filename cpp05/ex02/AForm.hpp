
#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>

class Bureaucrat;

class AForm  
{
    private:
        std::string const _formName;
        bool              _isSigned;
        int const         _gradeToSign;
        int const         _gradeToExecute;
    public:
        AForm(std::string const formName, int const gradeToSign, int const gradeToExecute);
        AForm(AForm const &other);
        AForm& operator=(const AForm &other);
        ~AForm();
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
        bool getAFormState() const;
        void beSigned(const Bureaucrat &bureaucrat);
        virtual int getGradeToSign() const;
        virtual int getGradeToExecute() const;
        void    throwException() const;
        void execute(Bureaucrat const & executor);        
        virtual void action() = 0;
};

std::ostream &operator<<(std::ostream &o, AForm const &i);

#endif
