#include <iostream>

int main(void)
{
    std::string hiThisIsBrain;
    std::string *stringPTR;

    hiThisIsBrain = "HI THIS IS BRAIN";
    stringPTR = &hiThisIsBrain;
    std::string &stringREF = hiThisIsBrain;

    std::cout << &hiThisIsBrain << std::endl;
    std::cout << &stringPTR << std::endl;
    std::cout << &stringREF << std::endl;

    std::cout << hiThisIsBrain << std::endl;
    std::cout << *stringPTR << std::endl;
    std::cout << stringREF << std::endl;

}