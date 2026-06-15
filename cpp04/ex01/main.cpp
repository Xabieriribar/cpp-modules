#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Animal* animals[6];
    int i = 0;

    std::cout << "=== polymorphic array ===" << std::endl;
    while (i < 3)
        animals[i++] = new Dog();
    while (i < 6)
        animals[i++] = new Cat();
    i = 0;
    while (i < 6)
    {
        animals[i]->makeSound();
        delete animals[i];
        i++;
    }
    std::cout << "=== deep-copy smoke test ===" << std::endl;
    Dog original;
    Dog copy(original);
    copy = original;
    return (0);
}
