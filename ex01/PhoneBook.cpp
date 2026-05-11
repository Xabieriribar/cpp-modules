#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <string>
#include <iostream>

void    PhoneBook::addContact()
{
    std::string first;
    std::string last;
    std::string nickname;
    std::string phonenumber;
    std::string darkest;
    Contact cntct;

    while (1)
    {
        std::cout << "Enter first name:";
        if (!std::getline(std::cin, first))
            break ;
        std::cout << "Enter last name:";
        if (!std::getline(std::cin, last))
            break ;
        std::cout << "Enter nickname:";
        if (!std::getline(std::cin, nickname))
            break ;
        std::cout << "Enter phone number:";
        if (!std::getline(std::cin, phonenumber))
            break ;
        std::cout << "Enter darkest secret:";
        if (!std::getline(std::cin, darkest))
            break ;
    }
    cntct.setContact(first, last, nickname, phonenumber);
}

void    PhoneBook::searchContact()
{
    std::string first;
    std::string last;
    std::string nickname;
    std::string phonenumber;
    std::string darkest;
    Contact cntct;

    while (1)
    {
        std::cout << "Enter first name:";
        if (!std::getline(std::cin, first))
            break ;
        std::cout << "Enter last name:";
        if (!std::getline(std::cin, last))
            break ;
        std::cout << "Enter nickname:";
        if (!std::getline(std::cin, nickname))
            break ;
        std::cout << "Enter phone number:";
        if (!std::getline(std::cin, phonenumber))
            break ;
        std::cout << "Enter darkest secret:";
        if (!std::getline(std::cin, darkest))
            break ;
    }
    cntct.setContact(first, last, nickname, phonenumber);
}