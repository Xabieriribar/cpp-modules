#include "B.hpp"

void B::identify(Base* p)
{
    B* b = dynamic_cast<B*>(p);
    if (b)
        std::cout << "B" << std::endl;
}