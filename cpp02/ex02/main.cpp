#include "Fixed.hpp"

int main( void ) 
{
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << "=== subject test ===" << std::endl;
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;

    std::cout << "=== operators ===" << std::endl;
    Fixed x(2);
    Fixed y(3);
    std::cout << "x < y: " << (x < y) << std::endl;
    std::cout << "x == y: " << (x == y) << std::endl;
    std::cout << "x + y: " << (x + y) << std::endl;
    std::cout << "x - y: " << (x - y) << std::endl;
    std::cout << "x * y: " << (x * y) << std::endl;
    std::cout << "y / x: " << (y / x) << std::endl;
    std::cout << "min: " << Fixed::min(x, y) << std::endl;
    return 0;
}
