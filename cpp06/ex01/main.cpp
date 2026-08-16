#include "Serializer.hpp"

#include <iostream>

int main()
{
    Data original;
    original.number = 42;
    original.text = "CPP06";

    uintptr_t raw = Serializer::serialize(&original);
    Data *restored = Serializer::deserialize(raw);

    std::cout << "original pointer:     " << &original << std::endl;
    std::cout << "deserialized pointer: " << restored << std::endl;
    std::cout << "same pointer:         "
              << (restored == &original ? "yes" : "no") << std::endl;
    std::cout << "data: " << restored->number << ", " << restored->text
              << std::endl;

    return (restored == &original ? 0 : 1);
}
