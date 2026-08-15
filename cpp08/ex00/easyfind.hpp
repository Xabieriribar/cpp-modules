#include <algorithm> 
#include <vector> 
#include <iostream> 
#include <stdexcept>

template <typename T>
void easyfind(T container, int number)
{
    T numberToFind = std::find(container.begin(), container.end(), number);

    try
    {
        if (numberToFind != container.end())
            std::cout  << *numberToFind<< std::endl;
        else
            throw std::runtime_error("Value not found");
    }
    catch (const exception& e)
    {
        std::cout << e.what() << std::endl;
    }
};