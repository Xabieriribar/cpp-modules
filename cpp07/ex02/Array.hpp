#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstdlib>
#include <iostream>
#include <string>

template <typename T>
class Array
{
    private:
        unsigned int _length;
        T *_array;
    public:
        Array() : _length(0), _array(new T[_length]) {}
        Array(unsigned int n) : _length(n), _array(new T[_length]) {}
        Array(Array const& other) : _length(other._length), _array(new T[_length]) 
        {
            unsigned int i = 0;
            while (i < _length)
            {
                _array[i] = other._array[i];
                i++;
            }
        }
        Array& operator=(Array const& other)
        {
            if (this != &other)
            {
                _length = other._length;
                unsigned int i = 0;
                while (i < _length)
                {
                    _array[i] = other._array[i];
                    i++;
                }
            }
            return (*this);
        }
        ~Array()
        {
            delete [] _array;
        }
        // T& operator=(const T& value)
        // {
        //     *this = value;
        //     return (*this);
        // }
        T& operator[](unsigned int index)
        {
            if (index >= 0 && index < _length)
                return (_array[index]);
            throw (std::exception());
        }
        unsigned int size()
        {
            return (_length);
        }
};
#endif