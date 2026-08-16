#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

class Span
{
    private:
        unsigned int _capacity;
        std::vector<int> _numbers;

    public:
        Span();
        Span(unsigned int n);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void addNumber(int number);

        template <typename Iterator>
        void addNumber(Iterator first, Iterator last)
        {
            Iterator it = first;
            unsigned int count = 0;

            while (it != last)
            {
                if (_numbers.size() + count >= _capacity)
                    throw std::runtime_error("Span capacity exceeded");
                ++count;
                ++it;
            }
            _numbers.insert(_numbers.end(), first, last);
        }

        template <typename Iterator>
        void addRange(Iterator first, Iterator last)
        {
            addNumber(first, last);
        }

        unsigned int shortestSpan() const;
        unsigned int longestSpan() const;
        unsigned int size() const;
        unsigned int capacity() const;
};

#endif
