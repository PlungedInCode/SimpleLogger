#ifdef LLOGGER_CPP_
#else 
#define Logger_CPP_


#include "../include/Logger.hpp"


// void Printer(std::ostream& out) {
//     out << '\n';
// };

// template <typename T, typename... Args>
// void Printer(std::ostream& out, T t, Args... args) {
//     out << t << " ";
//     Printer(out, args...);
// }

Logger::Logger() {
    log_filename_ = "log.txt";
    std::cout << log_filename_ << std::endl;
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::SetLogLevel(LogLevel log_level) {
    log_level_ = log_level;
}

void Logger::SetStream(OutputStream output) {
    output_ = output;
}

void Logger::SetLogFile(const std::string& log_filename) {
    log_filename_ = log_filename;
}

// template <typename... Args>
// void Logger::Trace(const Args&... args) {
//     if (log_level_ <= kTrace) {
//         Log(kTrace, args...);
//     }
// }

// template <typename... Args>
// void Logger::Log(LogLevel log_level, const Args&... args) {
//     std::string level_name = "[" + LogLevelNames[log_level] + "]";
//     Printer(std::cout, level_name, args...);
// }


#endif