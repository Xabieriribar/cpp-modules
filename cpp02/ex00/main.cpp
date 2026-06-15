#include "Fixed.hpp"

int main( void ) 
{
    Fixed a;
    Fixed b( a );
    Fixed c;

    c = b;

    std::cout << "a raw: " << a.getRawBits() << std::endl;
    std::cout << "b raw: " << b.getRawBits() << std::endl;
    std::cout << "c raw: " << c.getRawBits() << std::endl;

    return 0;
}
