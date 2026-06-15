#include "Harl.hpp"

int main(int argc, char **argv)
{
    Harl harl;

    if (argc != 2)
    {
        std::cerr << "Introduce only one level" << std::endl;
        return (2);
    }
    harl.complain(argv[1]);
    return (0);
}
