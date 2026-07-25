#include "iter.hpp"

int main(void)
{
    int array[] = {10, 20, 30};

    iter(array, 3, increase<int>);

    int i = 0;
    while (i < 3)
    {
        std::cout << array[i] << std::endl;
        i++;
    }
    return (0);
}