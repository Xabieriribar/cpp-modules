#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>
int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Intern intern;
    Bureaucrat boss("Boss", 1);
    AForm *forms[4];
    forms[0] = intern.makeForm("robotomy request", "Bender");
    forms[1] = intern.makeForm("shrubbery creation", "home");
    forms[2] = intern.makeForm("presidential pardon", "Arthur Dent");
    forms[3] = intern.makeForm("coffee request", "Nobody");
    for (int i = 0; i < 4; ++i) {
        if (forms[i]) {
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            delete forms[i];
        }
    }
    return 0;
}
