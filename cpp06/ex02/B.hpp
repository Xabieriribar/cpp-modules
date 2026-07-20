#ifndef B_HPP
#define B_HPP

#include "Base.hpp"

class B : public Base
{
    public:
        virtual ~B();
        void identify(Base* p);
};

#endif