#include "utility.hpp"

namespace utility {
    std::string removeDigitsBefore(std::string s) {
        unsigned int numberOfDigits = 0;
        for(const auto& character : s) {
            if(isdigit(character))
                numberOfDigits++;
        }
        s.erase(0, numberOfDigits);

        return s;
    }
}