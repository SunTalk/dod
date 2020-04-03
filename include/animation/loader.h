#pragma once

#include <nlohmann/json.hpp>

namespace nlo = nlohmann;

namespace rl {

class Animation;

// TODO

class AnimationLoader
{
public:
    AnimationLoader() = delete;

    static Animation loadFromString(const std::string &str);
    static Animation loadFromJson(const nlo::json &json);
    static std::string dumpFromObject(const Animation &obj);
};

}