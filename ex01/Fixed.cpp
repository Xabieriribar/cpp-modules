#include "Fixed.hpp"

Fixed::Fixed() : FixedPointNumber(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) : FixedPointNumber(value << Bits) 
{
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float fvalue) : FixedPointNumber((roundf(fvalue * (1 << Bits))))
{
    std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    this->FixedPointNumber = other.FixedPointNumber;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->FixedPointNumber = other.FixedPointNumber;
    return (*this);
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (FixedPointNumber);
}

void Fixed::setRawBits(int const raw)
{
    FixedPointNumber = raw;
}

int Fixed::toInt(void) const
{
    return (FixedPointNumber >> Bits);
}

float Fixed::toFloat(void) const
{
    return ((float)FixedPointNumber/(float)(1 <<Bits));
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
    o << i.toFloat();
    return (o);
}