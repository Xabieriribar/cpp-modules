#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include <ctime>

int main(void)
{
    std::cout << "=== subject test ===" << std::endl;
    std::srand(std::time(NULL));
    Intern someRandomIntern;
    AForm* rrf;
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");

    std::cout << "=== check if a bureaucrat can execute the correct request ===" << std::endl;

    Bureaucrat normalBureaucrat("Pepe", 1);
    normalBureaucrat.signAForm(*rrf);
    normalBureaucrat.executeForm(*rrf);

    std::cout << "=== send a non-existent form to an intern ===" << std::endl;

    rrf = someRandomIntern.makeForm("false request", "Bender");

    std::cout << "=== send a presidential pardon ===" << std::endl;

    rrf = someRandomIntern.makeForm("presidential pardon", "President");
    normalBureaucrat.signAForm(*rrf);
    normalBureaucrat.executeForm(*rrf);

    std::cout << "=== send a shrubbery request pardon ===" << std::endl;
    rrf = someRandomIntern.makeForm("shrubbery request", "President");
    if (rrf)
        normalBureaucrat.signAForm(*rrf);
    if (rrf)
        normalBureaucrat.executeForm(*rrf);

    delete (rrf);
    return (0);
}