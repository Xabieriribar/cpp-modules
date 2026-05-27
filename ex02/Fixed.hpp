#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int FixedPointNumber;
        static const int Bits = 8;
    public:
        Fixed();
        Fixed(const int value);
        Fixed(const float fvalue);
        ~Fixed();
        Fixed(const Fixed &other);

        Fixed &operator=(const Fixed &other);
        bool operator>(const Fixed &other) const;
        bool operator<(const Fixed &other) const;
        bool operator>=(const Fixed &other) const;
        bool operator<=(const Fixed &other) const;
        bool operator==(const Fixed &other) const;
        bool operator!=(const Fixed &other) const;

        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;
        static int min(Fixed &NumberOne, Fixed &NumberTwo);
        static int min(const Fixed &NumberOne, const Fixed &NumberTwo);
        static int max(Fixed &NumberOne, Fixed &NumberTwo);
        static int max(const Fixed &NumberOne, const Fixed &NumberTwo);
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif