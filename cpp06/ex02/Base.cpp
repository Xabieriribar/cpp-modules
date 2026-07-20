#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base * generate(void)
{
    int choice = std::rand() % 3;

    if (choice == 1)
        return (new A);
    if (choice == 2)
        return (new B);
    return (new C);
}

void identify(Base* p)
{

}