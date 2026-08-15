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
        MutantStack(const MutantStack& other) {}
        MutantStack& operator=(const MutantStack& other) {}
        ~MutantStack() {}
        typename std::stack<T>::container_type::iterator begin()
        {
            return (this->c.begin());
        }
        typename std::stack<T>::container_type::iterator end()
        {
            return (this->c.end());
        }
        class iterator
        {

        };



};

#endif