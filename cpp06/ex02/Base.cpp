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
    A* a = dynamic_cast<A*>(p);
    B* b = dynamic_cast<B*>(p);
    C* c = dynamic_cast<C*>(p);

    if (a != NULL)
    {
        std::cout << "A" << std::endl;
        return;
    }
    if (b != NULL)
    {
        std::cout << "B" << std::endl;
        return;
    }
    if (c != NULL)
    {
        std::cout << "C" << std::endl;
        return;
    }
    std::cout << "Unknown" << std::endl;
    return ;
}

void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return ;
    }
    catch (...)
    {
        try
        {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
        }
        catch (...)
        {
            try
            {
                (void)dynamic_cast<C&>(p);
                std::cout << "B" << std::endl;
            }
            catch (...)
            {
                std::cout << "Unknown" << std::endl;
            }
        }
    }
    
}

Base::~Base() {}