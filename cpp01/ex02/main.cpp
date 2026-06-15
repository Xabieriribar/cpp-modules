#include <iostream>

int main(void)
{
    std::string hiThisIsBrain;
    std::string *stringPTR;

    hiThisIsBrain = "HI THIS IS BRAIN";
    stringPTR = &hiThisIsBrain;
    std::string &stringREF = hiThisIsBrain;

    std::cout << "string address:   " << &hiThisIsBrain << std::endl;
    std::cout << "pointer address:  " << stringPTR << std::endl;
    std::cout << "reference address:" << &stringREF << std::endl;

    std::cout << "string value:   " << hiThisIsBrain << std::endl;
    std::cout << "pointer value:  " << *stringPTR << std::endl;
    std::cout << "reference value:" << stringREF << std::endl;
    return (0);
}
