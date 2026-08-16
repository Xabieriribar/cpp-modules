#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T *array, std::size_t length, F function)
{
    std::size_t i = 0;

    while (i < length)
    {
        function(array[i]);
        ++i;
    }
}

template <typename T, typename F>
void iter(const T *array, std::size_t length, F function)
{
    std::size_t i = 0;

    while (i < length)
    {
        function(array[i]);
        ++i;
    }
}

#endif
