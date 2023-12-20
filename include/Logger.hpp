#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <vector>
#include <string>
#include <iostream>


enum LogLevel {
    kTrace = 0,
    kDebug,
    kInfo,
    kWarning,
    kError,
};

const std::vector<std::string> LogLevelNames = {"TRACE", "DEBUG", "INFO", 
                                                "WARNING", "ERROR"};

enum OutputStream {
    kConsole,
    kFile,
    kBoth
};



class Logger {
public:
    static Logger& getInstance();

    static void SetLogLevel(LogLevel log_level);

    static void SetStream(OutputStream output);

    void SetLogFile(const std::string& log_filename);

    // template <typename... Args>
    // static void Trace(const Args&... args);

private:
    static LogLevel log_level_;
    static OutputStream output_;
    std::string log_filename_;

    
    // template <typename... Args>
    // static void Log(LogLevel log_level, const Args&... args);

    Logger();
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
};


#include "../src/Logger.cpp"
#endif //LOGGER_HPP