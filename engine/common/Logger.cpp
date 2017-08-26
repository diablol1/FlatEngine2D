#include "Logger.hpp"

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(Logger::MessageType messageType, const std::string& message) {
    if(!file.is_open())
        file.open("log.txt", std::ios::out | std::ios::trunc);

    std::string messageWithPrefix;

    if(messageType == MessageType::Info)
        messageWithPrefix += "[INFO]";
    else if(messageType == MessageType::Warning)
        messageWithPrefix += "[WARNING]";
    else if(messageType == MessageType::Error)
        messageWithPrefix += "[ERROR]";

    messageWithPrefix += (" " + message + "\n");

    file << messageWithPrefix;

    if(messageType == MessageType::Info)
        std::cout << messageWithPrefix;
    else if(messageType == MessageType::Warning)
        std::cout << termcolor::yellow << messageWithPrefix << termcolor::reset;
    else if(messageType == MessageType::Error)
        std::cout << termcolor::red << messageWithPrefix << termcolor::reset;
}