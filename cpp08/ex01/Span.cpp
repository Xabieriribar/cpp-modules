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

unsigned int Span::shortestSpan()
{
    if (!numbers.size() || numbers.size() == 1)
        throw std::runtime_error("There aren't enough numbers on this container");

    std::vector<unsigned int> copy_numbers = numbers;

    std::sort(copy_numbers.begin(), copy_numbers.end());

    std::vector<unsigned int>::iterator it = copy_numbers.begin();

    unsigned int temp_distance = *(it + 1) - *it;
    while (it != copy_numbers.end())
    {
        if (temp_distance > (*(it + 1) - *it))
            temp_distance = *(it + 1) - *it;
        ++it;
    }
    return temp_distance;
}

unsigned int Span::longestSpan()
{
    if (!numbers.size() || numbers.size() == 1)
        throw std::runtime_error("There are no numbers on this vector container");

    std::vector<unsigned int> copy_numbers = numbers;

    std::sort(copy_numbers.begin(), copy_numbers.end());

    std::vector<unsigned int>::iterator it = copy_numbers.begin();

    unsigned int max = *it;
    unsigned int min = *it;
    while (it != copy_numbers.end())
    {
        if ((it + 1) != copy_numbers.end() && max < *(it + 1))
            max = *(it + 1);
        if ((it + 1) != copy_numbers.end() && min > *(it + 1))
            min = *(it + 1);
        ++it;
    }
    unsigned int shortestSpan = max - min;
    return (shortestSpan);
}