#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int main(void)
{
    std::vector<int> values;
    values.push_back(10);
    values.push_back(20);
    values.push_back(30);
    values.push_back(20);

    try
    {
        std::vector<int>::iterator it = easyfind(values, 20);
        std::cout << "Found in vector: " << *it << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    const std::list<int> constValues(values.begin(), values.end());
    try
    {
        std::list<int>::const_iterator it = easyfind(constValues, 30);
        std::cout << "Found in const list: " << *it << std::endl;
        easyfind(constValues, 999);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
