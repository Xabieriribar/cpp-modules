#include "Span.hpp"

static void printTitle(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main(void)
{
    // ---------------------------------------------------------
    // TEST 1 — Subject example
    // ---------------------------------------------------------
    printTitle("Subject example");

    try
    {
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest:  " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Expected:
    // Shortest: 2
    // Longest:  14


    // ---------------------------------------------------------
    // TEST 2 — Unsorted numbers
    // ---------------------------------------------------------
    printTitle("Unsorted numbers");

    try
    {
        Span sp(4);

        sp.addNumber(100);
        sp.addNumber(1);
        sp.addNumber(55);
        sp.addNumber(60);

        std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest:  " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Sorted conceptually:
    // 1, 55, 60, 100
    //
    // Differences:
    // 54, 5, 40
    //
    // Expected:
    // Shortest: 5
    // Longest:  99


    // ---------------------------------------------------------
    // TEST 3 — Duplicate numbers
    // ---------------------------------------------------------
    printTitle("Duplicates");

    try
    {
        Span sp(4);

        sp.addNumber(42);
        sp.addNumber(10);
        sp.addNumber(42);
        sp.addNumber(100);

        std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest:  " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Expected:
    // Shortest: 0
    // Longest:  90


    // ---------------------------------------------------------
    // TEST 4 — Span with zero numbers
    // ---------------------------------------------------------
    printTitle("Empty Span");

    try
    {
        Span sp(5);

        std::cout << sp.shortestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception: "
                  << e.what() << std::endl;
    }

    // Expected:
    // An exception


    // ---------------------------------------------------------
    // TEST 5 — Span with only one number
    // ---------------------------------------------------------
    printTitle("One element");

    try
    {
        Span sp(5);

        sp.addNumber(42);

        std::cout << sp.shortestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception: "
                  << e.what() << std::endl;
    }

    // Expected:
    // An exception


    // ---------------------------------------------------------
    // TEST 6 — Exceed maximum capacity
    // ---------------------------------------------------------
    printTitle("Maximum capacity");

    try
    {
        Span sp(3);

        sp.addNumber(10);
        sp.addNumber(20);
        sp.addNumber(30);

        std::cout << "Trying to add fourth number..." << std::endl;

        sp.addNumber(40);

        std::cout << "ERROR: exception was not thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception: "
                  << e.what() << std::endl;
    }

    // Expected:
    // The fourth addNumber() throws an exception


    // ---------------------------------------------------------
    // TEST 7 — Capacity of zero
    // ---------------------------------------------------------
    printTitle("Zero capacity");

    try
    {
        Span sp(0);

        sp.addNumber(1);

        std::cout << "ERROR: exception was not thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception: "
                  << e.what() << std::endl;
    }

    // Expected:
    // addNumber() throws immediately


    // ---------------------------------------------------------
    // TEST 8 — Copy constructor
    // ---------------------------------------------------------
    printTitle("Copy constructor");

    try
    {
        Span original(3);

        original.addNumber(10);
        original.addNumber(20);
        original.addNumber(50);

        Span copy(original);

        std::cout << "Copy shortest: "
                  << copy.shortestSpan() << std::endl;

        std::cout << "Copy longest:  "
                  << copy.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Expected:
    // Copy shortest: 10
    // Copy longest:  40


    // ---------------------------------------------------------
    // TEST 9 — Assignment operator
    // ---------------------------------------------------------
    printTitle("Assignment operator");

    try
    {
        Span original(3);

        original.addNumber(5);
        original.addNumber(15);
        original.addNumber(100);

        Span copy(3);

        copy = original;

        std::cout << "Assigned shortest: "
                  << copy.shortestSpan() << std::endl;

        std::cout << "Assigned longest:  "
                  << copy.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Expected:
    // Assigned shortest: 10
    // Assigned longest:  95


    // ---------------------------------------------------------
    // TEST 10 — 10,000 numbers
    // ---------------------------------------------------------
    printTitle("10,000 numbers");

    try
    {
        Span sp(10000);

        for (int i = 0; i < 10000; ++i)
            sp.addNumber(i * 2);

        std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest:  " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Values:
    // 0, 2, 4, 6, ... 19998
    //
    // Expected:
    // Shortest: 2
    // Longest:  19998


    return (0);
}