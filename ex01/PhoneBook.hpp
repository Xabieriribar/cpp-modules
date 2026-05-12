#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
    private:
        Contact contacts[8]; 
        int     contactCount;
        int     nextIndex;
        int     emptyField;
    public:
        PhoneBook();
        void    addContact();
        void    searchContact();
        int     checkEmptyField();
};

#endif