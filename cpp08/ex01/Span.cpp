#include "Span.hpp"

Span::Span() : _capacity(0) {}

Span::Span(unsigned int n) : _capacity(n) {}

Span::Span(const Span &other)
    : _capacity(other._capacity), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _capacity = other._capacity;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _capacity)
        throw std::runtime_error("Span capacity exceeded");
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to compute a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int shortest = static_cast<unsigned int>(
        static_cast<double>(sorted[1]) - static_cast<double>(sorted[0]));

    for (std::size_t i = 1; i + 1 < sorted.size(); ++i)
    {
        unsigned int current = static_cast<unsigned int>(
            static_cast<double>(sorted[i + 1]) - static_cast<double>(sorted[i]));
        if (current < shortest)
            shortest = current;
    }
    return shortest;
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to compute a span");

    int minimum = *std::min_element(_numbers.begin(), _numbers.end());
    int maximum = *std::max_element(_numbers.begin(), _numbers.end());

    return static_cast<unsigned int>(
        static_cast<double>(maximum) - static_cast<double>(minimum));
}

unsigned int Span::size() const
{
    return static_cast<unsigned int>(_numbers.size());
}

unsigned int Span::capacity() const
{
    return _capacity;
}
