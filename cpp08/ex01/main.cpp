#include "Span.hpp"

int main()
{
    Span sp = Span(5);
    
    std::cout << "<<< ADDING NUMBER FUNCTIONALITY WITH SIZE 5 >>>" << std::endl;
    try
    {
        std::cout << "ADD NUMBER 1" << std::endl;
        sp.addNumber(6);
        std::cout << "ADD NUMBER 2" << std::endl;
        sp.addNumber(3);
        std::cout << "ADD NUMBER 3" << std::endl;
        sp.addNumber(17);
        std::cout << "ADD NUMBER 4" << std::endl;
        sp.addNumber(9);
        std::cout << "ADD NUMBER 5" << std::endl;
        sp.addNumber(11);
        std::cout << "ADD NUMBER 6 SHOULD THROW AN ERROR" << std::endl;
        sp.addNumber(12);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // std::cout << sp.shortestSpan() << std::endl;
    // std::cout << sp.longestSpan() << std::endl;
    return 0;
}