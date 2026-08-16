#include "Span.hpp"
#include <climits>
#include <iostream>
#include <vector>

int main(void)
{
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    Span bulk(10000);
    std::vector<int> values;
    for (int i = 0; i < 10000; ++i)
        values.push_back(i * 2);
    bulk.addNumber(values.begin(), values.end());
    std::cout << bulk.shortestSpan() << std::endl;
    std::cout << bulk.longestSpan() << std::endl;

    Span extremes(2);
    extremes.addNumber(INT_MIN);
    extremes.addNumber(INT_MAX);
    std::cout << extremes.longestSpan() << std::endl;

    try
    {
        sp.addNumber(42);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
