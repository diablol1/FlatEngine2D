#pragma once

#include <json.hpp>

using json = nlohmann::json;

class Serializable {
public:
    virtual void serialize(json &jsonData) const = 0;
    virtual void deserialize(const json& jsonData) = 0;
};