#include <iostream>
#include <string>
#include "PhoneBook.hpp"
#include "Contact.hpp"

int main ()
{
    std::string input;
    int         empty_flag;
    int         emptyField;
    PhoneBook pb;
    
    empty_flag = 1;
    emptyField = 0;
    while (1)
    {
        std::cout << "Enter command: ";
        if (!std::getline(std::cin, input))
            break ;
        if (input == "ADD")
        {
            pb.addContact();
            emptyField = pb.checkEmptyField();
            empty_flag = 0;
        }
        else if (input == "SEARCH" && emptyField == 0)
        {
            if (empty_flag == 0)
                pb.searchContact();
            else
                std::cout << "PhoneBook is empty" << std::endl;
        }
        else if (emptyField == 1)
        {
                std::cout << "Saved contacts cannot have empty fields" << std::endl;
                emptyField = 0;
        }
        else if (input == "EXIT")
            return 0;
    }
    return 0;

}