#include "Animation.hpp"

Animation::Animation(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::GetInstance().log(Logger::MessageType::Error,
                                  "Animation " + filename + " couldn't be loaded. Make sure it exists");
        return;
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    for (const auto& j : jsonData["Frames"]) {
        sf::IntRect location = sf::IntRect(j["location"]["left"],
                                           j["location"]["top"],
                                           j["location"]["width"],
                                           j["location"]["height"]);
        float startTime = j["startTime"];

        frames.emplace_back(startTime, location);
    }

    looped = jsonData["looped"];
}
unsigned int Animation::getNumberOfFrames() const {
    return static_cast<unsigned int>(frames.size());
}

const Frame& Animation::getFrame(int frameIndex) {
    return frames[frameIndex];
}

bool Animation::isLooped() const {
    return looped;
}
