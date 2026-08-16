#include "Base.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(std::time(NULL));

    for (int i = 0; i < 6; ++i)
    {
        Base *object = generate();
        std::cout << "pointer:   ";
        identify(object);
        std::cout << "reference: ";
        identify(*object);
        delete object;
    }
    return (0);
}
