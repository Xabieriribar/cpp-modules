#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <limits>
#include <string>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(ScalarConverter & other);
        ScalarConverter& operator=(ScalarConverter & other);
        ~ScalarConverter();

        static void printImpossible(std::string type);
        static void HandlePseudoLiterals(std::string input);
        static void HandleDoublePseudoLiterals(std::string input);
        static void DoubleToFloat(double nbr);
        static void HandleFloatPseudoLiterals(std::string input);
        static void FloatToDouble(float nbr);

    public:
        static void convert(std::string input);
};

#endif