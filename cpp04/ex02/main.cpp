#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Animal* animals[4];
    int i = 0;

    std::cout << "=== abstract base through pointers ===" << std::endl;
    while (i < 2)
        animals[i++] = new Dog();
    while (i < 4)
        animals[i++] = new Cat();
    i = 0;
    while (i < 4)
    {
        animals[i]->makeSound();
        delete animals[i];
        i++;
    }
    return (0);
}
