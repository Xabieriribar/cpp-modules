#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T> 
{
    private:
    public:
        MutantStack() {}
        MutantStack(const MutantStack& other) : std::stack<T>(other) {}
        MutantStack& operator=(const MutantStack& other) 
        {
            if (this != &other)
            {
                std::stack<T>::operator=(other);
            }
            return (*this);
        }
        ~MutantStack() {}
        typename std::stack<T>::container_type::iterator begin()
        {
            return (this->c.begin());
        }
        typename std::stack<T>::container_type::iterator end()
        {
            return (this->c.end());
        }
        typedef typename std::stack<T>::container_type::iterator iterator;

};

#endif