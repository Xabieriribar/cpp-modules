#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();
    delete(j);
    delete(i);
    delete(meta);

    const WrongAnimal* beta = new WrongAnimal();
    const WrongAnimal* x = new WrongCat();
    std::cout << x->getType() << " " << std::endl;
    x->makeSound(); //will output the animal sound because the virtual keyword is missing!
    beta->makeSound();
    delete(x);
    delete(beta);
    return 0;
}