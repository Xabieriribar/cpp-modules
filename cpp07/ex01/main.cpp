#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void print(const T &value)
{
    std::cout << value << std::endl;
}

template <typename T>
void increment(T &value)
{
    ++value;
}

int main()
{
    int numbers[] = {1, 2, 3, 4};
    const std::string words[] = {"templates", "are", "useful"};

    ::iter(numbers, 4, increment<int>);
    ::iter(numbers, 4, print<int>);
    ::iter(words, 3, print<std::string>);

    return 0;
}
