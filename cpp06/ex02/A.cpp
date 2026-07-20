#include "A.hpp"

void A::identify(Base* p)
{
    A* a = dynamic_cast<A*>(p);
    if (a)
        std::cout << "A" << std::endl;
}