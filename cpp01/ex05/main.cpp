#include "Harl.hpp"

int main(void)
{
    Harl harl;
    size_t index = 0;
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    while (index < 4)
    {
        std::cout << "[ " << levels[index] << " ]" << std::endl;
        harl.complain(levels[index]);
        index++;
    }
    std::cout << "[ INVALID ]" << std::endl;
    harl.complain("INVALID LEVEL");
    return (0);
}
