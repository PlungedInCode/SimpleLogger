#include "../include/Logger.hpp"

LogLevel Logger::log_level_ = LogLevel::kInfo;
OutputStream Logger::output_ = OutputStream::kConsole;
std::string Logger::log_filename_ = "log.txt";


Logger::Logger() {
}

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::SetLogLevel(const LogLevel& log_level) {
    log_level_ = log_level;
}

void Logger::SetStream(const OutputStream& output) {
    output_ = output;
}

void Logger::SetLogFile(const std::string& log_filename) {
    log_filename_ = log_filename;
}