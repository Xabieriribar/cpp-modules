#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(ScalarConverter & other);
        ScalarConverter& operator=(ScalarConverter & other);
        ~ScalarConverter();
    public:
        static void convert(std::string input);
};

#endif