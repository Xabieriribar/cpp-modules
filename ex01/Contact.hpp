#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
class Contact
{
    private:
        std::string  firstName;
        std::string  lastName;
        std::string  nickname;
        std::string  phoneNumber;
        std::string  darkestSecret;
    public:
        void setContact(std::string first, std::string last, std::string nick, std::string phone);
        std::string displayFirst();
        std::string displaySecond();
        std::string displayNick();
        std::string displayPhone();
};

#endif