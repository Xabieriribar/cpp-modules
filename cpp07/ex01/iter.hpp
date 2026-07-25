#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void increase(T& array)
{
    ++array;
}

template <typename T>
void iter(T address[], int length, void (*increase)(T& array))
{
    int i = 0;
    while (i < length)
    {
        increase(address[i]);
        i++;
    }
}

#endif