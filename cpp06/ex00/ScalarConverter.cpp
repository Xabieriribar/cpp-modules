#include "ScalarConverter.hpp"

void ScalarConverter::printImpossible(std::string type)
{
    std::cout << type << " : impossible" << std::endl;
}

void ScalarConverter::PrintNonDisplayable()
{
    std::cout << "Char : Non displayable\n";
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

void ScalarConverter::CharToFloat(char character)
{
    std::cout << "Float : " << static_cast<float>(character) << "f.0" << std::endl;
}

void ScalarConverter::CharToDouble(char character)
{
    std::cout << "Double : " << static_cast<double>(character) << ".0" << std::endl;
}

void ScalarConverter::CharToInt(char character)
{
    std::cout << "Int: " << static_cast<int>(character) << std::endl;
}

void ScalarConverter::HandleChars(char input)
{
    if (isprint(static_cast<unsigned char>(input)))
    {
        std::cout << "Char : '" << input << "'" << std::endl;
        CharToInt(input);
        CharToFloat(input);
        CharToDouble(input);
        return ;
    }
    else
    {
        printImpossible("Char");
        CharToInt(input);
        CharToFloat(input);
        CharToDouble(input);
        return ;
    }
}

bool ScalarConverter::IsBiggerThanMaxNumber(long value)
{
    if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max())
        return (false);
    return (true);
}
void ScalarConverter::IntToChar(int integer)
{
    if (isprint(integer))
        std::cout << "Char : '" << static_cast<char>(integer) << "'" << std::endl;
    else
        PrintNonDisplayable();
        
}

void ScalarConverter::IntToFloat(int integer)
{
    std::cout << "Float : " << static_cast<float>(integer) << "f" << std::endl;
}

void ScalarConverter::IntToDouble(int integer)
{
    std::cout << "Double : " << static_cast<double>(integer) << std::endl;
}

bool ScalarConverter::IsNumber(std::string input)
{
    char *end;
    char *end2;

    const char *str = input.c_str();
    strtol(str, &end, 10);
    if (!*end)
        return (true);
    if (*end == '.' && *end + 1 != '\0')
    {
        strtol(end + 1, &end2, 10);
        if (*end2 == 'f' && *end2 + 1 == '\0')
            return (true);
        if (*end2 && (*end2 == 'f' && *end2 + 1 != '\0'))
            return (false);
    }
    return (true);
}

bool ScalarConverter::IsInt(std::string input)
{
    char *end;
    strtol(input.c_str(), &end, 10);
    if (*end)
        return (false);
    return (true);
}
void ScalarConverter::PrintMax(long value)
{
    printImpossible("Char");
    printImpossible("Int");
    IntToFloat(value);
    IntToDouble(value);
}
void ScalarConverter::HandleNumbers(std::string input)
{
    if (IsInt(input))
    {
        long value = strtol(input.c_str(), NULL, 10);
        if (IsBiggerThanMaxNumber(value))
        {
            PrintMax(value);
            return ;
        }
        IntToChar(value);
        std::cout << "Int : " << value << std::endl;
        IntToFloat(value);
        IntToDouble(value);
        return ;
    }
    // if ((input.length() == 1 || input.length() == 2) && (isdigit(input[0]) && isdigit(input[1])))
    // {
    //     int value = static_cast<int>(input[0]);
    //     IntToChar(value);
    //     std::cout << "Int : " << value << std::endl;
    //     IntToFloat(value);
    //     IntToDouble(value);
    // }
}

void ScalarConverter::convert(std::string input)
{
    if (input == "nanf" || input == "nan" || input == "inf" || input == "inff" || input == "-inf" || input == "-inff")
    {
        HandlePseudoLiterals(input);
        return ;
    }
    if (input.length() == 1 && !isdigit(input[0])) 
    {
        HandleChars(input[0]);
        return ;
    }
    HandleNumbers(input);
}
