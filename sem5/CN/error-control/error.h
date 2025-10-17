#ifndef ERROR_H
#define ERROR_H

#include <string>

void injectSingleBitError(std::string &);
void injectTwoBitError(std::string &);
void injectBurstError(std::string &);
void injectOddError(std::string &);

#endif // ERROR_H