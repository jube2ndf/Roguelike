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
            case LogType::INFO: return "[INFO]";
            case LogType::WARNING: return "[WARNING]";
            case LogType::ERROR: return "[ERROR]";
            case LogType::FATAL: return "[FATAL]";
            default: return "[UNKNOWN]";
            }
        }
    };
}