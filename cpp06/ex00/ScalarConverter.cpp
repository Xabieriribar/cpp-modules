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
    std::cout << "float : " << "+" << static_cast<float>(nbr) << "f" << std::endl;
}

void ScalarConverter::FloatToDouble(float nbr)
{
    std::cout << "double : " << "+" << static_cast<double>(nbr) << std::endl;
}

void ScalarConverter::HandleFloatPseudoLiterals(std::string input)
{
    float value;

    if (input == "nanf")
    {
        value = std::numeric_limits<float>::quiet_NaN();
        std::cout << "float : " << value << "f" << std::endl;
        std::cout << "double : " << static_cast<double>(value) << std::endl;
        return ;
    }
    if (input == "+inff")
    {
        value = std::numeric_limits<float>::infinity();
        std::cout << "float : " << "+" << value << "f" << std::endl;
        FloatToDouble(value);
        return ;
    }
    if (input == "-inff")
    {
        value = -std::numeric_limits<float>::infinity();
        std::cout << "float : " << value << "f" << std::endl;
        std::cout << "double : " << static_cast<double>(value) << std::endl;
        return ;
    }
}
void ScalarConverter::HandleDoublePseudoLiterals(std::string input)
{
    double value;

    if (input == "nan")
    {
        value = std::numeric_limits<double>::quiet_NaN();
        std::cout << "float : " << static_cast<float>(value) << "f" << std::endl;
        std::cout << "double : " << value << std::endl;
        return ;
    }
    if (input == "+inf")
    {
        value = std::numeric_limits<double>::infinity();
        DoubleToFloat(value);
        std::cout << "double : " << "+" << value << std::endl;
        return ;
    }
    if (input == "-inf")
    {
        value = -std::numeric_limits<double>::infinity();
        std::cout << "float : " << static_cast<float>(value) << "f" << std::endl;
        std::cout << "double : " << value << std::endl;
        return ;
    }
}

void ScalarConverter::HandlePseudoLiterals(std::string input)
{
    printImpossible("int");
    printImpossible("char");
    if (input == "nan" || input == "+inf" || input == "-inf")
    {
        HandleDoublePseudoLiterals(input);
        return ;
    }
    if (input == "nanf" || input == "+inff" || input == "-inff")
    {
        HandleFloatPseudoLiterals(input);
        return ;
    }
}

void ScalarConverter::CharToFloat(char character)
{
    std::cout << "Float : " << static_cast<float>(character) << ".0f" << std::endl;
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
    if (value >= INT_MIN && value <= INT_MAX)
        return (false);
    return (true);
}
void ScalarConverter::IntToChar(int integer)
{
    if (integer >= -129 && integer <= 127)
    {
        if (isprint(integer))
            std::cout << "Char : '" << static_cast<char>(integer) << "'" << std::endl;
        else
            PrintNonDisplayable();
        return ;
    }
    printImpossible("char");
    
        
}

void ScalarConverter::IntToFloat(long integer)
{
    float value = static_cast<float>(integer);
    std::cout << "float : " << std::fixed << std::setprecision(1) << value << "f" << std::endl;
}

void ScalarConverter::IntToDouble(long integer)
{
    double value = static_cast<double>(integer);
    std::cout << "double : " << std::fixed << std::setprecision(1) << value << std::endl;
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
bool ScalarConverter::isFloat(std::string input)
{
    if (input.find('f') != std::string::npos)
        return (true);
    return (false);
}
// void ScalarConverter::floatToChar(std::string input)
// {


// }
void ScalarConverter::printDouble(std::string input)
{
    long value = strtol(input.c_str(), NULL, 10);
    double doubleValue = std::strtod(input.c_str(), NULL);
    float floatValue = static_cast<float>(doubleValue);
    IntToChar(value);
    std::cout << "Int : " << value << std::endl;
    std::cout.unsetf(std::ios::floatfield);
    if (floatValue == std::floor(value))
    {
        std::cout << "Float : ";
        std::cout <<
        std::fixed <<
        std::setprecision(1) << 
        floatValue <<
        "f" <<
        std::endl;
        std::cout << "Double : ";
        std::cout <<
        std::fixed <<
        std::setprecision(1) << 
        floatValue <<
        std::endl;
        return ;
    }
    std::cout << "Float : " << std::setprecision(std::numeric_limits<float>::digits10) << floatValue << "f" << std::endl;
    std::cout << "Double : " << std::setprecision(std::numeric_limits<double>::digits10) << doubleValue << std::endl;

}

void ScalarConverter::printFloat(std::string input)
{
    long value = strtol(input.c_str(), NULL, 10);
    double doubleValue = std::strtod(input.c_str(), NULL);
    float floatValue = static_cast<float>(doubleValue);
    IntToChar(value);
    std::cout << "Int : " << value << std::endl;
    std::cout.unsetf(std::ios::floatfield);
    if (floatValue == std::floor(value))
    {
        std::cout << "Float : ";
        std::cout <<
        std::fixed <<
        std::setprecision(1) << 
        floatValue <<
        "f" <<
        std::endl;
        std::cout << "Double : ";
        std::cout <<
        std::fixed <<
        std::setprecision(1) << 
        floatValue <<
        std::endl;
        return ;
    }
    std::cout << "Float : " << std::setprecision(std::numeric_limits<float>::digits10) << floatValue << "f" << std::endl;
    std::cout << "Double : " << std::setprecision(std::numeric_limits<double>::digits10) << doubleValue << std::endl;

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
    else if (!isFloat(input))
    {
        printDouble(input);
        return ;
    }
    else
    {
        printFloat(input);
    }
    // else if (IsNumber(input))
    // {
    //     if (isFloat(input))
    //     {
    //         floatToChar(input);
    //     }
    // }
    // if ((input.length() == 1 || input.length() == 2) && (isdigit(input[0]) && isdigit(input[1])))
    // {
    //     int value = static_cast<int>(input[0]);
    //     IntToChar(value);
    //     std::cout << "Int : " << value << std::endl;
    //     IntToFloat(value);
    //     IntToDouble(value);
    // }
}

bool ScalarConverter::isNotDigit(std::string input)
{
    int i = 0;
    int sign_counter = 0;
    int sign_index = 0;
    int point_counter = 0;
    int point_index = 0;
    int float_index = 0;
    int float_counter = 0;

    while (input[i])
    {
        if (input[i] == '+' || input[i] == '-')
        {
            sign_counter++;
            sign_index = i;
        }
        if (input[i] == '.')
        {
            point_counter++;
            point_index = i;
        }
        if (input[i] == 'f')
        {
            float_counter++;
            float_index = i;
        }
        i++;
    }
    if (point_counter == 0)
        point_index++;
    if (sign_counter == 2 || sign_index != 0 || point_counter == 2 || point_index == 0 || float_counter == 2)
    {
        return (true);
    }
    i = 0;
    while (input[i])
    {
        if (!isdigit(input[i]) && input[i] != '+' && input[i] != '-' && input[i] != '.' && input[i] != 'f')
        {
            printf("what");
            return (true);
        }
        i++;
    }
    return (false);
}
void ScalarConverter::convert(std::string input)
{
    if (input == "")
        return ;
    if (input == "nanf" || input == "nan" || input == "+inf" || input == "+inff" || input == "-inf" || input == "-inff")
    {
        HandlePseudoLiterals(input);
        return ;
    }
    if (input.length() == 1 && !isdigit(input[0])) 
    {
        HandleChars(input[0]);
        return ;
    }
    if (isNotDigit(input))
    {
        printImpossible("char");
        printImpossible("int");
        printImpossible("float");
        printImpossible("double");
        return ;
    }
    HandleNumbers(input);
}
