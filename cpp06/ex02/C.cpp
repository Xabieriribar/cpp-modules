#include "C.hpp"

void C::identify(Base* p)
{
    C* c = dynamic_cast<C*>(p);
    if (c)
        std::cout << "C" << std::endl;
}