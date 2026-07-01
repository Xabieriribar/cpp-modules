#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(ScalarConverter & other);
        ScalarConverter& operator=(ScalarConverter & other);
        ~ScalarConverter();

        static void printImpossible(std::string type);

        static void HandlePseudoLiterals(std::string input);
        static void HandleChars(char input);
        static void HandleDoublePseudoLiterals(std::string input);

        static void DoubleToFloat(double nbr);
        static void CharToDouble(char character);
        static void CharToInt(char character);
        static void CharToFloat(char character);
        static void HandleFloatPseudoLiterals(std::string input);
        static void FloatToDouble(float nbr);
        static void HandleNumbers(std::string input);
        static void IntToChar(int integer);
        static void IntToFloat(int integer);
        static void IntToDouble(int integer);


    public:
        static void convert(std::string input);
};

#endif