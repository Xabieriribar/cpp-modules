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
        this->FixedPointNumber = other.getRawBits();
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
    return ((float)FixedPointNumber/(float)(1 << Bits));
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
    o << i.toFloat();
    return (o);
}

bool Fixed::operator>(const Fixed &other) const
{
    if (this->getRawBits() > other.getRawBits())
        return (true);
    else
        return (false);
}

bool Fixed::operator<(const Fixed &other) const
{
    if (this->getRawBits() < other.getRawBits())
        return (true);
    else
        return (false);
}

bool Fixed::operator>=(const Fixed &other) const
{
    if (this->getRawBits() >= other.getRawBits())
        return (true);
    else
        return (false);
}

bool Fixed::operator<=(const Fixed &other) const
{
    if (this->getRawBits() <= other.getRawBits())
        return (true);
    else
        return (false);
}

bool Fixed::operator==(const Fixed &other) const
{
    if (this->getRawBits() == other.getRawBits())
        return (true);
    else
        return (false);
}

bool Fixed::operator!=(const Fixed &other) const
{
    if (this->getRawBits() != other.getRawBits())
        return (true);
    else
        return (false);
}

int  Fixed::operator*(const Fixed &other) const
{
    float x = this->toFloat();
    float y = other.toFloat();
    Fixed x_object(x);
    Fixed y_object(x);
    std::cout << "This is it: " << x << std::endl;
    float result = x * y;

    
    return ();
}

int  Fixed::operator/(const Fixed &other) const
{
    return (this->FixedPointNumber / other.getRawBits());
}

int  Fixed::operator+(const Fixed &other) const
{
    return (this->FixedPointNumber + other.getRawBits());
}

int  Fixed::operator-(const Fixed &other) const
{
    return (this->FixedPointNumber - other.getRawBits());
}


Fixed &Fixed::operator++(void)
{
    this->FixedPointNumber += 1;
    return (*this);
}
Fixed Fixed::operator++(int)
{
    Fixed copy(*this);

    this->FixedPointNumber += 1;
    return (copy);
}

Fixed &Fixed::min(Fixed &NumberOne, Fixed &NumberTwo)
{
    if (NumberOne < NumberTwo)
        return (NumberOne);
    else
        return (NumberTwo);
}

Fixed const &Fixed::min(const Fixed &NumberOne, const Fixed &NumberTwo)
{
    if (NumberOne < NumberTwo)
        return (NumberOne);
    else
        return (NumberTwo);
}

Fixed &Fixed::max(Fixed &NumberOne, Fixed &NumberTwo)
{
    if (NumberTwo > NumberOne)
        return (NumberTwo);
    else
        return (NumberOne);
}

Fixed const &Fixed::max(const Fixed &NumberOne, const Fixed &NumberTwo)
{
    if (NumberTwo > NumberOne)
        return (NumberTwo);
    else
        return (NumberOne);
}
