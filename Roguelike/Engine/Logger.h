#pragma once
#include "EngineAPI.h"
#include "ILogSink.h"
#include <memory>
#include <vector>

namespace GameEngine {
    class ENGINE_API Logger
    {
    public:
        Logger() = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& Instance()
        {
            static Logger logger;
            return logger;
        }

        void AddSink(std::unique_ptr<ILogSink> sink)
        {
            m_Sinks.push_back(std::move(sink));
        }

        void Log(
            LogType type,
            std::string_view category,
            const char* file,
            const char* function,
            uint32_t line,
            std::string_view message)
        {
            LogMessage logMessage
            {
                type,
                category,
                std::string(message),
                file,
                function,
                line,
                std::chrono::system_clock::now()
            };

            for (auto& sink : m_Sinks)
            {
                sink->Write(logMessage);
            }
        }

    private:
        std::vector<std::unique_ptr<ILogSink>> m_Sinks;
    };
}

#define LOG(type, category, text) \
    GameEngine::Logger::Instance().Log( \
        type, \
        category, \
        __FILE__, \
        __FUNCTION__, \
        __LINE__, \
        text)

#define LOG_INFO(category, text) LOG(GameEngine::LogType::Info, category, text)

#define LOG_WARN(category, text) LOG(GameEngine::LogType::Warning, category, text)

#define LOG_ERROR(category, text) LOG(GameEngine::LogType::Error, category, text)

#define LOG_FATAL(category, text) LOG(GameEngine::LogType::Fatal, category, text)
