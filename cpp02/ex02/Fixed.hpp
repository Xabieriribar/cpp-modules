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
        Fixed operator++(int);
        Fixed &operator++(void);
        Fixed operator--(int);
        Fixed &operator--(void);
        bool operator>(const Fixed &other) const;
        bool operator<(const Fixed &other) const;
        bool operator>=(const Fixed &other) const;
        bool operator<=(const Fixed &other) const;
        bool operator==(const Fixed &other) const;
        bool operator!=(const Fixed &other) const;
        
        Fixed operator*(const Fixed &other) const;
        Fixed operator/(const Fixed &other) const;
        Fixed operator+(const Fixed &other) const;
        Fixed operator-(const Fixed &other) const;

        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;
        static Fixed &min(Fixed &NumberOne, Fixed &NumberTwo);
        static const Fixed &min(const Fixed &NumberOne, const Fixed &NumberTwo);
        static Fixed &max(Fixed &NumberOne, Fixed &NumberTwo);
        static const Fixed &max(const Fixed &NumberOne, const Fixed &NumberTwo);
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif