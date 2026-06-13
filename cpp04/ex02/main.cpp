#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Animal* AnimalObjects[10];
    const Animal *AnimalObject = new Animal();
    int i = 0;


    while (i < 5)
        AnimalObjects[i++] = new Dog();
    while (i < 10)
        AnimalObjects[i++] = new Cat();
    i = 0;
    //Tests for exercise 02
    //First, lets make sure our AnimalObjects are still able to bark or meow
    AnimalObjects[0]->makeSound(); //Should bark
    AnimalObjects[5]->makeSound(); //Should meow
    //Second, lets make sure the Animal pointer is not able to speak
    AnimalObject->makeSound();
    while (i < 10)
    {
        delete(AnimalObjects[i]);
        i++;
    }
    return (0);
}
