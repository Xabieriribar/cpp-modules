#include "sedIsForLosers.hpp"

void findWord(std::string line, std::string toFind, int indexAfterMatch, size_t &startPosition)
{
    startPosition = line.find(toFind, indexAfterMatch);
}