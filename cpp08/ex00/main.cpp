#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

int  main(void)
{
    std::vector<int> numbers;
    std::vector<int>::iterator it;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    it = numbers.begin();

    while (it != numbers.end())
    {
        std::cout  << *it << std::endl;
        ++it;
    }
    std::vector<int>::iterator numberToFind = std::find(numbers.begin(), numbers.end(), 100);
    try
    {
        if (numberToFind != numbers.end())
            std::cout  << *numberToFind<< std::endl;
        else
            throw std::runtime_error("Value not found");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}