#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>

int main()
{
    std::cout << "=== Valid construction ===" << std::endl;

    try
    {
        Bureaucrat alice("Alice", 42);
        Form contract("Contract", 50, 25);

        std::cout << alice << std::endl;
        std::cout << contract << std::endl;

        std::cout << "Form name: " << contract.getName() << std::endl;
        std::cout << "Signed: " << contract.getFormState() << std::endl;
        std::cout << "Grade required to sign: "
                  << contract.getGradeToSign() << std::endl;
        std::cout << "Grade required to execute: "
                  << contract.getGradeToExecute() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid signing grade: too high ===" << std::endl;

    try
    {
        Form invalid("Invalid", 0, 50);
        std::cout << invalid << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid signing grade: too low ===" << std::endl;

    try
    {
        Form invalid("Invalid", 151, 50);
        std::cout << invalid << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid execution grade: too high ===" << std::endl;

    try
    {
        Form invalid("Invalid", 50, 0);
        std::cout << invalid << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Invalid execution grade: too low ===" << std::endl;

    try
    {
        Form invalid("Invalid", 50, 151);
        std::cout << invalid << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Successful signing with beSigned() ===" << std::endl;

    try
    {
        Bureaucrat manager("Manager", 25);
        Form document("Document", 30, 10);

        std::cout << "Before: " << document << std::endl;

        document.beSigned(manager);

        std::cout << "After:  " << document << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Failed signing with beSigned() ===" << std::endl;

    try
    {
        Bureaucrat intern("Intern", 100);
        Form document("Important document", 50, 25);

        std::cout << "Before: " << document << std::endl;

        document.beSigned(intern);

        std::cout << "After:  " << document << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Bureaucrat::signForm success ===" << std::endl;

    try
    {
        Bureaucrat director("Director", 10);
        Form authorization("Authorization", 20, 5);

        director.signForm(authorization);

        std::cout << authorization << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Bureaucrat::signForm failure ===" << std::endl;

    try
    {
        Bureaucrat employee("Employee", 80);
        Form authorization("Authorization", 20, 5);

        employee.signForm(authorization);

        std::cout << authorization << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception escaped signForm(): "
                  << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Signing an already signed form ===" << std::endl;

    try
    {
        Bureaucrat director("Director", 10);
        Form authorization("Authorization", 20, 5);

        director.signForm(authorization);
        director.signForm(authorization);

        std::cout << authorization << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Copy constructor ===" << std::endl;

    try
    {
        Bureaucrat director("Director", 10);
        Form original("Original", 20, 5);

        director.signForm(original);

        Form copy(original);

        std::cout << "Original: " << original << std::endl;
        std::cout << "Copy:     " << copy << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
