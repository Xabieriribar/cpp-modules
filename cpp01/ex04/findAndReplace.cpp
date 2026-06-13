#include "sedIsForLosers.hpp"

void findWord(std::string line, std::string toFind, int indexAfterMatch, size_t &startPosition)
{
    startPosition = line.find(toFind, indexAfterMatch);
}

void getNextLine(std::string &newLine, std::string line, int startPosition, char **argv)
{
    std::string beforeMatch;
    std::string afterMatch;
    int         s1_len;

    s1_len = std::string (argv[2]).length();
    beforeMatch = line.substr(0, startPosition);
    afterMatch = line.substr(startPosition + s1_len);
    newLine = beforeMatch + argv[3] + afterMatch;
}