#ifndef RANDOMSTRING_H
#define RANDOMSTRING_H

#include <algorithm>
#include <random>
#include <string>

#include "node.h"

inline std::string randomString()
{
    static std::default_random_engine generator;

    std::string toReturn(8, ' ');

    std::uniform_int_distribution<int> randomASCIIPrintable(33,122);

    std::generate(
        toReturn.begin(),
        toReturn.end(),
        [&randomASCIIPrintable] {
            return static_cast<char>(randomASCIIPrintable(generator));
        }
    );

    return toReturn;
}

#endif // RANDOMSTRING_H
