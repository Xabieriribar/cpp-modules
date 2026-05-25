#include "sedIsForLosers.hpp"

int main(int argc, char **argv)
{
    std::string  line;

    if (argc != 4)
    {
        std::cerr << "Usage: ./sedIsForLosers [Name of the input file] [Word to find] [Word to substitute it with]" << std::endl;
        return (2);
    }
    if (std::string (argv[2]).empty())
    {
        std::cerr << "The search term is empty" << std::endl;
        return (2);
    }
    std::ifstream inFile(argv[1]);
    if (!inFile)
    {
        std::cerr << "Infile error" << std::endl;
        return (2);
    }
    std::string outFileName = std::string (argv[1]) + ".replace";
    std::ofstream outFile(outFileName.c_str());
    if (!outFile)
    {
        std::cerr << "Outfile error" << std::endl;
        return (2);
    }
    size_t s2_len = std::string (argv[3]).length();
    std::string newLine;
    while (std::getline(inFile, line))
    {
        size_t startPosition = 0;
        size_t indexAfterMatch = 0;
        while (startPosition != std::string::npos)
        {
            findWord(line, argv[2], indexAfterMatch, startPosition);
            if (startPosition == std::string::npos)
            {
                newLine = line;
                break;
            }
            getNextLine(newLine, line, startPosition, argv);
            indexAfterMatch = startPosition + s2_len;
            line = newLine;
        }
        outFile << newLine << std::endl;
    }
    return 0;

}