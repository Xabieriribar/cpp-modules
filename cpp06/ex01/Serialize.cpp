#include "Serializer.hpp"

Serializer::Serializer()
{

}
Serializer::Serializer(Serializer & other) {}
Serializer& Serializer::operator=(Serializer & Other)
{
    return (*this);
}

Serializer::~Serializer(){}

uintptr_t Serializer::serialize(Data* ptr)
{
    uintptr_t address;

    address = reinterpret_cast<uintptr_t>(ptr);
    return (address);

}
Data* Serializer::deserialize(uintptr_t raw)
{
    Data *deserialized_address;

    deserialized_address = reinterpret_cast<Data *>(raw);
    return (deserialized_address);

}