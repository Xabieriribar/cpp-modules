#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
    std::srand(std::time(NULL));
    Intern someRandomIntern;
    AForm* rrf;
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    Bureaucrat someRandomBureaucrat("Pepo", 1);
    someRandomBureaucrat.signAForm(*rrf);
    someRandomBureaucrat.executeForm(*rrf);
    delete (rrf);
    return (0);
}