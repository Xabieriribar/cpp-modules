#include <cctype>
#include <iostream>

int main(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    if (argc == 1)
        return (std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl, 0);
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            std::cout << static_cast<char>(std::toupper(argv[i][j]));
            j++;
        }
        i++;
    }
    std::cout << std::endl;
    return (0);
}