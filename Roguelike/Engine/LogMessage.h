#pragma once
#include <string>
#include <chrono>
#include "LogType.h"

namespace GameEngine {
    struct LogMessage
    {
        LogType Type;

        std::string_view Category;
        std::string Text;

        const char* File;
        const char* Function;

        uint32_t Line;

        std::chrono::system_clock::time_point Time;
    };
}