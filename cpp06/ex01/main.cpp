#include "Serializer.hpp"
#include "Data.hpp"
#include <stdlib.h>

int main(void)
{
    Data* object = new(Data);
    uintptr_t serialized_object;

    object->names = "Xabi";
    object->numbers = 10;
    serialized_object = Serializer::serialize(object);
    Data *deserialized_object = Serializer::deserialize(serialized_object);
    if (deserialized_object == object)
    {
        std::cout << "Transformation succeeded\n";
        return (0);
    }
    return (0);
}