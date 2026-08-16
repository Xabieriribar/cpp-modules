#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &other);
        ScalarConverter &operator=(const ScalarConverter &other);
        ~ScalarConverter();

        static bool isPseudoLiteral(const std::string &literal);
        static bool isCharLiteral(const std::string &literal);
        static bool isIntLiteral(const std::string &literal);
        static bool isFloatLiteral(const std::string &literal);
        static bool isDoubleLiteral(const std::string &literal);

        static void printPseudoLiteral(const std::string &literal);
        static void printChar(char value);
        static void convertIntLiteral(const std::string &literal);
        static void convertFloatLiteral(const std::string &literal);
        static void convertDoubleLiteral(const std::string &literal);
        static void printFromDouble(double value, bool doubleOverflow);
        static void printImpossible();
        static void printFloatValue(float value);
        static void printDoubleValue(double value);

    public:
        static void convert(const std::string &literal);
};

#endif
