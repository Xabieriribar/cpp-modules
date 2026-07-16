#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(std::time(NULL));

    Intern intern;
    Bureaucrat boss("Boss", 1);

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 1: CREATE ROBOTOMY FORM" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* robotomy =
        intern.makeForm("robotomy request", "Bender");

    if (robotomy != NULL)
    {
        std::cout << *robotomy << std::endl;

        boss.signAForm(*robotomy);
        boss.executeForm(*robotomy);

        delete robotomy;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 2: CREATE SHRUBBERY FORM" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* shrubbery =
        intern.makeForm("shrubbery creation", "garden");

    if (shrubbery != NULL)
    {
        std::cout << *shrubbery << std::endl;

        boss.signAForm(*shrubbery);
        boss.executeForm(*shrubbery);

        delete shrubbery;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 3: CREATE PRESIDENTIAL FORM" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* pardon =
        intern.makeForm("presidential pardon", "Arthur Dent");

    if (pardon != NULL)
    {
        std::cout << *pardon << std::endl;

        boss.signAForm(*pardon);
        boss.executeForm(*pardon);

        delete pardon;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 4: INVALID FORM NAME" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* invalid =
        intern.makeForm("coffee request", "Evaluator");

    if (invalid == NULL)
        std::cout << "Invalid form correctly returned NULL." << std::endl;
    else
        delete invalid;

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 5: CASE-SENSITIVE INVALID NAME" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* wrongCase =
        intern.makeForm("Robotomy Request", "Bender");

    if (wrongCase == NULL)
        std::cout << "Case-sensitive name correctly rejected." << std::endl;
    else
        delete wrongCase;

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 6: LOW-GRADE BUREAUCRAT" << std::endl;
    std::cout << "========================================" << std::endl;

    AForm* difficultForm =
        intern.makeForm("presidential pardon", "Marvin");

    if (difficultForm != NULL)
    {
        Bureaucrat internGrade("Weak bureaucrat", 150);

        internGrade.signAForm(*difficultForm);
        internGrade.executeForm(*difficultForm);

        delete difficultForm;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 7: INTERN COPY CONSTRUCTOR" << std::endl;
    std::cout << "========================================" << std::endl;

    Intern copiedIntern(intern);

    AForm* copiedForm =
        copiedIntern.makeForm("robotomy request", "Copied Bender");

    if (copiedForm != NULL)
    {
        boss.signAForm(*copiedForm);
        boss.executeForm(*copiedForm);

        delete copiedForm;
    }

    return 0;
}
