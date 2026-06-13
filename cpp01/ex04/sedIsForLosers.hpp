#ifndef SEDISFORLOSERS_HPP
#define SEDISFORLOSERS_HPP

#include <iostream>
#include <fstream>

void findWord(std::string line, std::string toFind, int indexAfterMatch, size_t &startPosition);
void getNextLine(std::string &newLine, std::string line, int startPosition, char **argv);

#endif 