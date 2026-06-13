#include "Harl.hpp"

Harl::Harl()
{
    levels[0] = "DEBUG";
    levels[1] = "INFO";
    levels[2] = "WARNING";
    levels[3] = "ERROR";
    TestFlag = true;
    NumberOfLevels = 4;
}

bool Harl::getFlag()
{
    if (TestFlag)
        return (true);
    else
        return (false);
}

void Harl::debug (void)
{
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}
void Harl::info  (void)
{
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;

}
void Harl::warning (void)
{
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::error (void)
{
    std::cout << "This is unacceptable! I want to speak to the manager now" << std::endl;
}
void Harl::complain(std::string level)
{
    size_t Index = 0;
    void (Harl::*pointer_array[4])(void);

    pointer_array[0] = &Harl::debug;
    pointer_array[1] = &Harl::info;
    pointer_array[2] = &Harl::warning;
    pointer_array[3] = &Harl::error;
    while (Index != NumberOfLevels && level != levels[Index])
        Index++;
    switch (Index)
    {
        case 0:
            std::cout << "[DEBUG]" << std::endl;
            (this->*pointer_array[0])();
            std::cout << std::endl;
        case 1:
            std::cout << "[INFO]" << std::endl;
            (this->*pointer_array[1])();
            std::cout << std::endl;
        case 2:
            std::cout << "[WARNING]" << std::endl;
            (this->*pointer_array[2])();
            std::cout << std::endl;
        case 3:
            std::cout << "[ERROR]" << std::endl;
            (this->*pointer_array[3])();
            std::cout << std::endl;
            break ;
        default:
            std::cout << "[Probably complaining about insignificant problems]" << std::endl;
            break ;
    }
}