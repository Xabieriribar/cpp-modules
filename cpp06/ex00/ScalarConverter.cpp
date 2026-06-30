#include "ScalarConverter.hpp"

void ScalarConverter::printImpossible(std::string type)
{
    std::cout << type << " : impossible" << std::endl;
}

void ScalarConverter::DoubleToFloat(double nbr)
{
    std::cout << "float : " << static_cast<float>(nbr) << "f" << std::endl;
}

void ScalarConverter::FloatToDouble(float nbr)
{
    std::cout << "double : " << static_cast<double>(nbr) << std::endl;
}

void ScalarConverter::HandleFloatPseudoLiterals(std::string input)
{
    float value;

    if (input == "nanf")
    {
        value = std::numeric_limits<float>::quiet_NaN();
        FloatToDouble(value);
        std::cout << "float : " << value << "f" << std::endl;
        return ;
    }
    if (input == "inff")
    {
        value = std::numeric_limits<float>::infinity();
        FloatToDouble(value);
        std::cout << "float : " << value << "f" << std::endl;
        return ;
    }
    if (input == "-inff")
    {
        value = -std::numeric_limits<float>::infinity();
        FloatToDouble(value);
        std::cout << "float : " << value << "f" << std::endl;
        return ;
    }
}
void ScalarConverter::HandleDoublePseudoLiterals(std::string input)
{
    double value;

    if (input == "nan")
    {
        value = std::numeric_limits<double>::quiet_NaN();
        DoubleToFloat(value);
        std::cout << "double : " << value << std::endl;
        return ;
    }
    if (input == "inf")
    {
        value = std::numeric_limits<double>::infinity();
        DoubleToFloat(value);
        std::cout << "double : " << value << std::endl;
        return ;
    }
    if (input == "-inf")
    {
        value = -std::numeric_limits<double>::infinity();
        DoubleToFloat(value);
        std::cout << "double : " << value << std::endl;
        return ;
    }
}

void ScalarConverter::HandlePseudoLiterals(std::string input)
{
    printImpossible("int");
    printImpossible("char");
    if (input == "nan" || input == "inf" || input == "-inf")
    {
        HandleDoublePseudoLiterals(input);
        return ;
    }
    if (input == "nanf" || input == "inff" || input == "-inff")
    {
        HandleFloatPseudoLiterals(input);
        return ;
    }
}

void ScalarConverter::convert(std::string input)
{
    if (input == "nanf" || input == "nan" || input == "inf" || input == "inff" || input == "-inf" || input == "-inff")
        HandlePseudoLiterals(input);
}
