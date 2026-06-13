#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    Animal animals[2];
    Dog dogs[2];
    Cat cats[2];
    WrongAnimal wrongAnimals[2];
    WrongCat wrongCats[2];

    std::cout << "[ARRAYS OK]" << std::endl;
    return 0;
}
