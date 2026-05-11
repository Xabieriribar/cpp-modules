#include <iostream>
#include <string>
#include "PhoneBook.hpp"
#include "Contact.hpp"

int main (int argc, char **argv)
{
    std::string input;
    PhoneBook pb;
    

    if (argc != 1)
        return 0;
    while (1)
    {
        std::cout << "Enter command:";
        if (!std::getline(std::cin, input))
            break ;
        if (input == "ADD")
            pb.addContact();
        if (input == "SEARCH")
            pb.searchContact();
    }

}