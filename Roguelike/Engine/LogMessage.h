#pragma once
#include <string>
#include <chrono>
#include "LogType.h"

namespace GameEngine {
    struct LogMessage
    {
        LogType Type;

        std::string Category;
        std::string Text;

        std::string File;
        std::string Function;

        uint32_t Line;

        std::chrono::system_clock::time_point Time;
    };
}