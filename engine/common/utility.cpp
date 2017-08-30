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

    bool isFileEmpty(std::ifstream& file) {
        return file.peek() == std::ifstream::traits_type::eof();
    }
}