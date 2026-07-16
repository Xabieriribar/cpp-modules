#include "Bureaucrat.hpp"
#include <exception>

int main()
{
    std::cout << "=== Valid construction ===" << std::endl;

    try
    {
        Bureaucrat alice("Alice", 42);

        std::cout << alice << std::endl;
        std::cout << "Name: " << alice.getName() << std::endl;
        std::cout << "Grade: " << alice.getGrade() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Grade too high in constructor ===" << std::endl;

    try
    {
        Bureaucrat tooHigh("TooHigh", 0);
        std::cout << tooHigh << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Grade too low in constructor ===" << std::endl;

    try
    {
        Bureaucrat tooLow("TooLow", 151);
        std::cout << tooLow << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Increment grade ===" << std::endl;

    try
    {
        Bureaucrat bob("Bob", 3);

        std::cout << "Before: " << bob << std::endl;
        bob.increment();
        std::cout << "After:  " << bob << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Decrement grade ===" << std::endl;

    try
    {
        Bureaucrat charlie("Charlie", 148);

        std::cout << "Before: " << charlie << std::endl;
        charlie.decrement();
        std::cout << "After:  " << charlie << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Increment past grade 1 ===" << std::endl;

    try
    {
        Bureaucrat boss("Boss", 1);

        std::cout << "Before: " << boss << std::endl;
        boss.increment();
        std::cout << "After:  " << boss << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Decrement past grade 150 ===" << std::endl;

    try
    {
        Bureaucrat intern("Intern", 150);

        std::cout << "Before: " << intern << std::endl;
        intern.decrement();
        std::cout << "After:  " << intern << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Object remains valid after exception ===" << std::endl;

    Bureaucrat limit("Limit", 1);

    try
    {
        limit.increment();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "Current state: " << limit << std::endl;

    return 0;
}
