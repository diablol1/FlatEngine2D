#pragma once

#include <string>
#include <fstream>
#include <typeinfo>

namespace utility {

    std::string removeDigitsBefore(std::string s);

    template<typename Type>
    std::string getClassName() {
        std::string name = typeid(Type).name();

        return removeDigitsBefore(name);
    }
    template<typename Type>
    std::string getClassName(const Type& obj) {
        std::string name = typeid(obj).name();

        return removeDigitsBefore(name);
    }

    template<typename Type>
    std::size_t getClassHashCode() {
        return typeid(Type).hash_code();
    }
    template<typename Type>
    std::size_t getClassHashCode(const Type& obj) {
        return typeid(obj).hash_code();
    }

    bool isFileEmpty(std::ifstream& file);
}