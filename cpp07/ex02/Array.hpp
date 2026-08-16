#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Array
{
private:
    unsigned int _size;
    T *_data;

public:
    Array() : _size(0), _data(NULL)
    {
    }

    explicit Array(unsigned int n) : _size(n), _data(NULL)
    {
        if (_size != 0)
            _data = new T[_size]();
    }

    Array(const Array &other) : _size(other._size), _data(NULL)
    {
        if (_size != 0)
        {
            _data = new T[_size]();
            try
            {
                for (unsigned int i = 0; i < _size; ++i)
                    _data[i] = other._data[i];
            }
            catch (...)
            {
                delete [] _data;
                _data = NULL;
                _size = 0;
                throw;
            }
        }
    }

    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            T *newData = NULL;

            if (other._size != 0)
            {
                newData = new T[other._size]();
                try
                {
                    for (unsigned int i = 0; i < other._size; ++i)
                        newData[i] = other._data[i];
                }
                catch (...)
                {
                    delete [] newData;
                    throw;
                }
            }
            delete [] _data;
            _data = newData;
            _size = other._size;
        }
        return *this;
    }

    ~Array()
    {
        delete [] _data;
    }

    T &operator[](unsigned int index)
    {
        if (index >= _size)
            throw std::out_of_range("Array index out of bounds");
        return _data[index];
    }

    const T &operator[](unsigned int index) const
    {
        if (index >= _size)
            throw std::out_of_range("Array index out of bounds");
        return _data[index];
    }

    unsigned int size() const
    {
        return _size;
    }
};

#endif
