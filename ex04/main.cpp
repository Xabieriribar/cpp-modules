#include "sedIsForLosers.hpp"

int main(int argc, char **argv)
{
    std::string  outFileName;
    std::string  line;

    if (argc != 4)
        return (1);
    std::ifstream inFile(argv[1]);
    if (!argv[1])
        return (1);
    outFileName = std::string (argv[1]) + ".replace";
    std::ofstream outFile(outFileName.c_str());
    std::cout << "Compilation succeeded" << std::endl;
    while (std::getline(inFile, line))
    {
        findWord(inFile);
    }
    return 0;

}