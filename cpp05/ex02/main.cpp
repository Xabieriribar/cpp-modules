#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Bureaucrat boss("Boss", 1);
    Bureaucrat low("Low", 150);
    ShrubberyCreationForm shrubbery("garden");
    RobotomyRequestForm robotomy("Bender");
    PresidentialPardonForm pardon("Arthur Dent");
    low.signForm(shrubbery);
    low.executeForm(shrubbery);
    boss.signForm(shrubbery);
    boss.executeForm(shrubbery);
    boss.signForm(robotomy);
    boss.executeForm(robotomy);
    boss.signForm(pardon);
    boss.executeForm(pardon);
    return 0;
}
