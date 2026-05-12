#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

int     PhoneBook::checkEmptyField()
{
    if (emptyField)
    {
        emptyField = 0;
        return 1;
    }
    return 0;
}

PhoneBook::PhoneBook()
{
    nextIndex = 0;
    contactCount = 0;
    emptyField = 0;
}
void    PhoneBook::addContact()
{
    std::string first;
    std::string last;
    std::string nickname;
    std::string phonenumber;
    std::string darkest;

    std::cout << "Enter first name: ";
    if (!std::getline(std::cin, first))
        return;
    std::cout << "Enter last name: ";
    if (!std::getline(std::cin, last))
        return;
    std::cout << "Enter nickname: ";
    if (!std::getline(std::cin, nickname))
        return;
    std::cout << "Enter phone number: ";
    if (!std::getline(std::cin, phonenumber))
        return;
    std::cout << "Enter darkest secret: ";
    if (!std::getline(std::cin, darkest))
        return;
    if (first == ""|| last == ""|| nickname == "" || phonenumber == "" || darkest == "")
    {
        emptyField = 1;
        return ;
    }
    contacts[nextIndex].setContact(first, last, nickname, phonenumber);
    nextIndex++;
    if (nextIndex == 8)
        nextIndex = 0;
    if (contactCount != 8)
        contactCount++;
}

static std::string formatColumn(std::string text)
{
    if (text.length() > 10)
        return text.substr(0, 9) + ".";
    return text;
}

void    PhoneBook::searchContact()
{
    std::string first;
    std::string last;
    std::string nickname;
    std::string phonenumber;
    std::string secret;
    int index = 0;

    std::cout << std::right << std::setw(10) << "index" << "|"
            << std::right << std::setw(10) << "first name" << "|"
            << std::right << std::setw(10) << "last name" << "|"
            << std::right << std::setw(10) << "nickname"
            << std::endl;
    while (index < contactCount)
    {
        first = contacts[index].displayFirst();
        last = contacts[index].displaySecond();
        nickname = contacts[index].displayNick();
        std::cout << std::right << std::setw(10) << index << "|"
                << std::right << std::setw(10) << formatColumn(first) << "|"
                << std::right << std::setw(10) << formatColumn(last) << "|"
                << std::right << std::setw(10) << formatColumn(nickname)
                << std::endl;
        index++;
    }
    index = contactCount + 1;
    while (1)
    {
        std::string user_index;
        std::cout << "Enter a valid index: " << std::endl;
        if (!std::getline(std::cin, user_index))
            return;
        if (user_index.length() == 1 && std::isdigit(user_index[0]))
        {
            index = user_index[0] - '0';
            if (index < contactCount)
                break;
        }
        std::cout << "That is not a valid index, try again" << std::endl;
    }
    first = contacts[index].displayFirst();
    last = contacts[index].displaySecond();
    nickname = contacts[index].displayNick();
    phonenumber = contacts[index].displayPhone();
    secret = contacts[index].displaySecret();
    std::cout << std::right << std::setw(10) << "index" << "|"
            << std::right << std::setw(10) << "first name" << "|"
            << std::right << std::setw(10) << "last name" << "|"
            << std::right << std::setw(10) << "nickname" << "|"
            << std::right << std::setw(10) << "phone number" << "|"
            << std::right << std::setw(10) << "darkest secret"
            << std::endl;
    std::cout << std::right << std::setw(10) << index << "|"
            << std::right << std::setw(10) << formatColumn(first) << "|"
            << std::right << std::setw(10) << formatColumn(last) << "|"
            << std::right << std::setw(10) << formatColumn(nickname) << "|"
            << std::right << std::setw(10) << formatColumn(phonenumber) << "|"
            << std::right << std::setw(10) << formatColumn(secret)
            << std::endl;
}