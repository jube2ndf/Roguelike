#pragma once
#include <string>
#include "LogType.h"
#include "LogMessage.h"

namespace GameEngine {
    class ILogSink
    {
    public:
        virtual ~ILogSink() = default;

        virtual void Write(const LogMessage& message) = 0;
    protected:
        std::string logLevelToString(LogType level) {
            switch (level) {
            case LogType::Info: return "[INFO]";
            case LogType::Warning: return "[WARNING]";
            case LogType::Error: return "[ERROR]";
            case LogType::Fatal: return "[FATAL]";
            default: return "[UNKNOWN]";
            }
        }
    };
}