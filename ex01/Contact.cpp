#include <string>
#include "Contact.hpp"
#include "PhoneBook.hpp"

void Contact::setContact(std::string first, std::string last, std::string nick, std::string phone)
{
    firstName = first;
    lastName = last;
    nickname = nick;
    phoneNumber = phone;
}

std::string Contact::displayFirst()
{
    std::string Firstname;

    Firstname = firstName;
    return Firstname;
}

std::string Contact::displayNick()
{
    std::string Nickname;

    Nickname = nickname;
    return Nickname;
}

std::string Contact::displaySecond()
{
    std::string Second;

    Second = lastName;
    return Second;
}

std::string Contact::displayPhone()
{
    std::string Phone;

    Phone = phoneNumber;
    return Phone;
}