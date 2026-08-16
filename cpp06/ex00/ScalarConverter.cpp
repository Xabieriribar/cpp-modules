#include "ScalarConverter.hpp"

#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return (*this);
}
ScalarConverter::~ScalarConverter() {}

static bool allDigits(const std::string &s, std::string::size_type start,
                      std::string::size_type end)
{
    if (start >= end)
        return (false);
    for (std::string::size_type i = start; i < end; ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return (false);
    }
    return (true);
}

bool ScalarConverter::isPseudoLiteral(const std::string &literal)
{
    return (literal == "nan" || literal == "+inf" || literal == "-inf"
        || literal == "nanf" || literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isCharLiteral(const std::string &literal)
{
    return (literal.length() == 1
        && !std::isdigit(static_cast<unsigned char>(literal[0])));
}

bool ScalarConverter::isIntLiteral(const std::string &literal)
{
    if (literal.empty())
        return (false);
    std::string::size_type start = 0;
    if (literal[0] == '+' || literal[0] == '-')
        start = 1;
    return (allDigits(literal, start, literal.length()));
}

bool ScalarConverter::isFloatLiteral(const std::string &literal)
{
    if (literal.length() < 3 || literal[literal.length() - 1] != 'f')
        return (false);

    std::string body = literal.substr(0, literal.length() - 1);
    std::string::size_type start = 0;
    if (!body.empty() && (body[0] == '+' || body[0] == '-'))
        start = 1;
    if (start >= body.length())
        return (false);

    std::string::size_type dot = body.find('.', start);
    if (dot == std::string::npos || body.find('.', dot + 1) != std::string::npos)
        return (false);

    bool before = (dot > start) && allDigits(body, start, dot);
    bool after = (dot + 1 < body.length())
        && allDigits(body, dot + 1, body.length());
    return (before || after);
}

bool ScalarConverter::isDoubleLiteral(const std::string &literal)
{
    if (literal.empty())
        return (false);

    std::string::size_type start = 0;
    if (literal[0] == '+' || literal[0] == '-')
        start = 1;
    if (start >= literal.length())
        return (false);

    std::string::size_type dot = literal.find('.', start);
    if (dot == std::string::npos
        || literal.find('.', dot + 1) != std::string::npos)
        return (false);

    bool before = (dot > start) && allDigits(literal, start, dot);
    bool after = (dot + 1 < literal.length())
        && allDigits(literal, dot + 1, literal.length());
    return (before || after);
}

void ScalarConverter::printPseudoLiteral(const std::string &literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

void ScalarConverter::printFloatValue(float value)
{
    if (std::floor(value) == value)
        std::cout << std::fixed << std::setprecision(1) << value << "f";
    else
        std::cout << value << "f";
    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::setprecision(6);
}

void ScalarConverter::printDoubleValue(double value)
{
    if (std::floor(value) == value)
        std::cout << std::fixed << std::setprecision(1) << value;
    else
        std::cout << value;
    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::setprecision(6);
}

void ScalarConverter::printChar(char value)
{
    int numeric = static_cast<unsigned char>(value);
    if (std::isprint(static_cast<unsigned char>(value)))
        std::cout << "char: '" << value << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << numeric << std::endl;
    std::cout << "float: ";
    printFloatValue(static_cast<float>(numeric));
    std::cout << std::endl;
    std::cout << "double: ";
    printDoubleValue(static_cast<double>(numeric));
    std::cout << std::endl;
}

static void printCharFromNumber(double value)
{
    if (value < static_cast<double>(INT_MIN)
        || value > static_cast<double>(INT_MAX))
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }
    int truncated = static_cast<int>(value);
    if (truncated < 0 || truncated > 127)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }
    char c = static_cast<char>(truncated);
    if (!std::isprint(static_cast<unsigned char>(c)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << c << "'" << std::endl;
}

void ScalarConverter::convertIntLiteral(const std::string &literal)
{
    errno = 0;
    char *end = NULL;
    long parsed = std::strtol(literal.c_str(), &end, 10);

    if (errno == ERANGE || end == literal.c_str() || *end != '\0'
        || parsed < INT_MIN || parsed > INT_MAX)
    {
        errno = 0;
        end = NULL;
        double fallback = std::strtod(literal.c_str(), &end);
        bool overflow = (errno == ERANGE || end == literal.c_str() || *end != '\0');
        printFromDouble(fallback, overflow);
        return;
    }

    int value = static_cast<int>(parsed);
    printCharFromNumber(static_cast<double>(value));
    std::cout << "int: " << value << std::endl;
    std::cout << "float: ";
    printFloatValue(static_cast<float>(value));
    std::cout << std::endl;
    std::cout << "double: ";
    printDoubleValue(static_cast<double>(value));
    std::cout << std::endl;
}

void ScalarConverter::convertFloatLiteral(const std::string &literal)
{
    std::string numeric = literal.substr(0, literal.length() - 1);
    errno = 0;
    char *end = NULL;
    double parsed = std::strtod(numeric.c_str(), &end);
    bool parseOverflow = (errno == ERANGE || end == numeric.c_str() || *end != '\0');

    if (parseOverflow
        || (std::fabs(parsed) > static_cast<double>(std::numeric_limits<float>::max())
            && parsed != 0.0))
    {
        printFromDouble(parsed, parseOverflow);
        return;
    }

    float value = static_cast<float>(parsed);
    printCharFromNumber(static_cast<double>(value));
    double widened = static_cast<double>(value);
    if (widened < static_cast<double>(INT_MIN)
        || widened > static_cast<double>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

    std::cout << "float: ";
    printFloatValue(value);
    std::cout << std::endl;
    std::cout << "double: ";
    printDoubleValue(static_cast<double>(value));
    std::cout << std::endl;
}

void ScalarConverter::convertDoubleLiteral(const std::string &literal)
{
    errno = 0;
    char *end = NULL;
    double value = std::strtod(literal.c_str(), &end);
    bool overflow = (errno == ERANGE || end == literal.c_str() || *end != '\0');
    printFromDouble(value, overflow);
}

void ScalarConverter::printFromDouble(double value, bool doubleOverflow)
{
    if (doubleOverflow)
        std::cout << "char: impossible" << std::endl;
    else
        printCharFromNumber(value);

    if (doubleOverflow || value < static_cast<double>(INT_MIN)
        || value > static_cast<double>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

    std::cout << "float: ";
    if (doubleOverflow
        || (std::fabs(value) > static_cast<double>(std::numeric_limits<float>::max())
            && value != 0.0))
        std::cout << "impossible";
    else
        printFloatValue(static_cast<float>(value));
    std::cout << std::endl;

    std::cout << "double: ";
    if (doubleOverflow)
        std::cout << "impossible";
    else
        printDoubleValue(value);
    std::cout << std::endl;
}

void ScalarConverter::printImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
    if (literal.empty())
    {
        printImpossible();
        return;
    }

    if (isPseudoLiteral(literal))
    {
        printPseudoLiteral(literal);
        return;
    }

    if (isCharLiteral(literal))
    {
        printChar(literal[0]);
        return;
    }

    if (isIntLiteral(literal))
    {
        convertIntLiteral(literal);
        return;
    }
    if (isFloatLiteral(literal))
    {
        convertFloatLiteral(literal);
        return;
    }
    if (isDoubleLiteral(literal))
    {
        convertDoubleLiteral(literal);
        return;
    }

    printImpossible();
}
