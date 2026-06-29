#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(std::time(NULL));

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 1: EXECUTE AN UNSIGNED FORM" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat executor("Executor", 1);
        ShrubberyCreationForm form("garden");

        executor.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 2: SIGNING GRADE TOO LOW" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat lowGrade("LowGrade", 150);
        ShrubberyCreationForm form("garden");

        lowGrade.signAForm(form);
        std::cout << form << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 3: SHRUBBERY SUCCESS" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat gardener("Gardener", 137);
        ShrubberyCreationForm form("home");

        std::cout << "Before signing:" << std::endl;
        std::cout << form << std::endl;

        gardener.signAForm(form);

        std::cout << "After signing:" << std::endl;
        std::cout << form << std::endl;

        gardener.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 4: SIGNED BUT EXECUTOR GRADE TOO LOW" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat signer("Signer", 70);
        Bureaucrat weakExecutor("WeakExecutor", 100);
        RobotomyRequestForm form("Bender");

        signer.signAForm(form);
        weakExecutor.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 5: ROBOTOMY SUCCESS OR FAILURE" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat surgeon("Surgeon", 45);
        RobotomyRequestForm form("Bender");

        surgeon.signAForm(form);

        for (int i = 0; i < 10; ++i)
        {
            std::cout << "Robotomy attempt " << i + 1 << ":" << std::endl;
            surgeon.executeForm(form);
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 6: PRESIDENTIAL FORM - SIGN FAILURE" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat employee("Employee", 26);
        PresidentialPardonForm form("Arthur Dent");

        employee.signAForm(form);
        employee.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 7: PRESIDENTIAL FORM - EXECUTION FAILURE" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat president("President", 25);
        Bureaucrat minister("Minister", 6);
        PresidentialPardonForm form("Arthur Dent");

        president.signAForm(form);
        minister.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 8: PRESIDENTIAL FORM SUCCESS" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat president("President", 1);
        PresidentialPardonForm form("Arthur Dent");

        president.signAForm(form);
        president.executeForm(form);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST 9: POLYMORPHIC EXECUTION" << std::endl;
    std::cout << "========================================" << std::endl;

    {
        Bureaucrat boss("Boss", 1);

        ShrubberyCreationForm shrubbery("park");
        RobotomyRequestForm robotomy("Marvin");
        PresidentialPardonForm pardon("Ford Prefect");

        AForm* forms[3];

        forms[0] = &shrubbery;
        forms[1] = &robotomy;
        forms[2] = &pardon;

        for (int i = 0; i < 3; ++i)
        {
            std::cout << "\nForm " << i + 1 << ":" << std::endl;
            boss.signAForm(*forms[i]);
            boss.executeForm(*forms[i]);
        }
    }

    return 0;
}
