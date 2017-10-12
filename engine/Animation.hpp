#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include "lib/json.hpp"

#include "common/Logger.hpp"
#include "Frame.hpp"

class Animation {
public:
    explicit Animation(const std::string& filename);

    unsigned int getNumberOfFrames() const;
    const Frame& getFrame(int frameIndex);
    bool isLooped() const;
private:
    std::vector<Frame> frames;
    bool looped;
};