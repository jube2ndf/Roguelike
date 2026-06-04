#pragma once
#include "ILogSink.h"
namespace GameEngine {
    class ConsoleSink :
        public ILogSink
    {
    public:
        void Write(const LogMessage& message) override
        {
            std::cout << this->logLevelToString(message.Type)
                << message.Text << std::endl;
        }
    };
}
