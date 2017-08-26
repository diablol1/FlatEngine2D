#pragma once

#include "lib/termcolor.hpp"

#include <iostream>
#include <fstream>
#include <unordered_map>

class Logger {
public:
    static Logger& GetInstance();

    enum class MessageType {
        Info,
        Warning,
        Error
    };

    void log(MessageType messageType, const std::string& message);

private:
    Logger() = default;

    std::ofstream file;
};