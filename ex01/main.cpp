#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Animal* AnimalObjects[10];
    int i = 0;


    while (i < 5)
        AnimalObjects[i++] = new Dog();
    while (i < 10)
        AnimalObjects[i++] = new Cat();
    i = 0;
    while (i < 10)
    {
        delete(AnimalObjects[i]);
        i++;
    }
    return (0);
}
