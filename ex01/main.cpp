#include <iostream>
#include <string>
#include "PhoneBook.hpp"
#include "Contact.hpp"

int main ()
{
    std::string input;
    PhoneBook pb;
    
    while (1)
    {
        std::cout << "Enter command: ";
        if (!std::getline(std::cin, input))
            break ;
        if (input == "ADD")
        {
            pb.addContact();
        }
        if (input == "SEARCH")
            pb.searchContact();
    }

}