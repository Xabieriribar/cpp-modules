#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void)
{
    Intern someRandomIntern;
    AForm* rrf;
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    Bureaucrat someRandomBureaucrat("Pepo", 1);
    someRandomBureaucrat.signAForm(*rrf);
    someRandomBureaucrat.executeForm(*rrf);
    delete (rrf);
    return (0);
}