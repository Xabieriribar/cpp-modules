#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <stdint.h>
#include <stdio.h>

class Serializer
{
    private:
        Serializer();
        Serializer(Serializer & other);
        Serializer& operator=(Serializer & Other);
        ~Serializer();
    public:
        static uintptr_t serialize(Data *ptr);
        static Data* deserialize(uintptr_t raw);

};
#endif