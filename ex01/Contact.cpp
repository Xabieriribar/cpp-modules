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
    if (Firstname == "")
        return "";
    return Firstname;
}

std::string Contact::displayNick()
{
    std::string Nickname;

    Nickname = nickname;
    if (Nickname == "")
        return "";
    return Nickname;
}

std::string Contact::displaySecond()
{
    std::string Second;

    Second = lastName;
    if (Second == "")
        return "";
    return Second;
}

std::string Contact::displayPhone()
{
    std::string Phone;

    Phone = phoneNumber;
    if (Phone == "")
        return "";
    return Phone;
}

std::string Contact::displaySecret()
{
    std::string Secret;

    Secret = darkestSecret;
    if (Secret == "")
        return "";
    return Secret;
}