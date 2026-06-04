#pragma once
#include <ostream>
#include <fstream>
#include "ILogSink.h"
namespace GameEngine {
    class FileSink :
        public ILogSink
    {
    public:
        explicit FileSink(const std::string& filename)
            : m_File(filename, std::ios::app)
        {}

        void Write(const LogMessage& message) override
        {
            m_File << this->logLevelToString(message.Type)
                << "[" << message.Category << "] "
                << message.Text
                << " (" << message.File << ":"
                << message.Line << ")"
                << std::endl;;
        }

    private:
        std::ofstream m_File;
    };
}
