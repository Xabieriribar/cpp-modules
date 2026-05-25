#include "Harl.hpp"

int main(void)
{
    Harl harl;
    size_t Index = 0;
    size_t NumberOfLevels = 4;
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    while (Index < NumberOfLevels)
    {
        harl.complain(levels[Index]);
        if (!harl.getFlag())
            return (2);
        Index++;
    }
    harl.complain("INVALID LEVEL");
    if (!harl.getFlag())
        return (2);
    return (0);
}