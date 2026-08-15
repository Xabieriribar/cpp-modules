#include "Span.hpp"

Span::Span(unsigned int N) : _n(N) {}

Span::Span(const Span& other) : _n(other._n), numbers(other.numbers) {}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _n = other._n;
        numbers = other.numbers;
    }
    return (*this);
}

Span::~Span() {}

void Span::addNumber(int nbr)
{
    if (numbers.size() >= _n)
        throw std::runtime_error("Maximum amount of numbers allowed reached");
    numbers.push_back(nbr);
}

void Span::shortestSpan(int nbr)
{
    std::vector<unsigned int> copy_numbers = numbers;

    std::sort(copy_numbers.begin(), copy_numbers.end());

    std::vector<unsigned int>::iterator it = copy_numbers.begin();

    while (it != copy_numbers.end())
    {
        std::vector<unsigned int>::iterator temp_it = it + 1;
        ++it;
    }


}