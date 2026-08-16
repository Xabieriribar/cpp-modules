#include "Array.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define MAX_VAL 750

int main()
{
    Array<int> numbers(MAX_VAL);
    int *mirror = new int[MAX_VAL];

    std::srand(std::time(NULL));
    for (int i = 0; i < MAX_VAL; ++i)
    {
        const int value = std::rand();
        numbers[i] = value;
        mirror[i] = value;
    }

    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
        if (tmp.size() != numbers.size() || test.size() != numbers.size())
        {
            delete [] mirror;
            return 1;
        }
    }

    for (int i = 0; i < MAX_VAL; ++i)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "copy did not preserve values" << std::endl;
            delete [] mirror;
            return 1;
        }
    }

    try
    {
        numbers[-2] = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    Array<int> small(2);
    small[0] = 7;
    small[1] = 8;
    small = numbers;
    if (small.size() != numbers.size() || small[100] != numbers[100])
    {
        delete [] mirror;
        return 1;
    }

    Array<int> initialized(5);
    for (unsigned int i = 0; i < initialized.size(); ++i)
    {
        if (initialized[i] != 0)
        {
            std::cerr << "elements were not value-initialized" << std::endl;
            delete [] mirror;
            return 1;
        }
    }

    const Array<int> constCopy(numbers);
    std::cout << "const access sample: " << constCopy[0] << std::endl;

    delete [] mirror;
    return 0;
}
