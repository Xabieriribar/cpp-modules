#include "sedIsForLosers.hpp"

int main(int argc, char **argv)
{
    std::string  outFileName;
    std::string  line;
    size_t       startPosition;
    std::string  beforeMatch;
    std::string  afterMatch;
    std::string  newLine;
    int         s1_len;
    int         s2_len;
    int         indexAfterMatch;

    if (argc != 4)
    {
        std::cout << "Usage: ./sedIsForLosers [Name of the input file] [Word to find] [Word to substitute it with]" << std::endl;
        return (1);
    }
    std::ifstream inFile(argv[1]);
    if (!inFile)
    {
        std::cout << "Infile error";
        return (1);
    }
    outFileName = std::string (argv[1]) + ".replace";
    std::ofstream outFile(outFileName.c_str());
    if (!outFile)
    {
        std::cout << "Outfile error";
        return (1);
    }
    s1_len = std::string (argv[2]).length();
    s2_len = std::string (argv[3]).length();
    while (std::getline(inFile, line))
    {
        startPosition = 0;
        indexAfterMatch = 0;
        while (startPosition != std::string::npos)
        {
            findWord(line, argv[2], indexAfterMatch, startPosition);
            std::cout << "Yiha";
            if (startPosition == std::string::npos)
            {
                std::cout << "Entramos para " << newLine <<  std::endl;
                break;
            }
            beforeMatch = line.substr(indexAfterMatch, startPosition);
            indexAfterMatch = startPosition + s2_len;
            afterMatch = line.substr(startPosition + s1_len);
            newLine = beforeMatch + argv[3] + afterMatch;
            line = newLine;
            std::cout << newLine << std::endl;
        }
        outFile << newLine << std::endl;
    }
    return 0;

}