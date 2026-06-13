#include "Harl.hpp"

int main(int argc, char **argv)
{
    Harl harl;
    size_t Index = 0;
    size_t NumberOfLevels = 4;

    if (argc != 2)
    {
        std::cerr << "Introduce only one level" << std::endl;
        return (2);
    }
    harl.complain(argv[1]);
    return (0);
}