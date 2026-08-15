#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

class Span
{
    private:
        unsigned int _n;
        std::vector<unsigned int> numbers;
    public:
        Span(unsigned int N);
        Span(const Span& other);
        Span& operator=(const Span& other);
        ~Span();

        void addNumber(int nbr);
        void shortestSpan(int nbr);
        void longestSpan(int nbr);
};

#endif