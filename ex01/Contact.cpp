#include <string>
#include "Contact.hpp"

void    Contact::setContact(std::string first, std::string last, std::string nick, std::string phone)
{
    Contact contact;

    contact.firstName = first;
    contact.lastName = last;
    contact.nickname = nick;
    contact.phoneNumber = phone;
}