#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <vector>

#define RESET_COLOR "\033[0m"
#define NO_COLOR ""
#define IN_FILE "in file "
#define ON_LINE ":"

enum LogLevel {
  kTrace = 0,
  kDebug,
  kInfo,
  kWarning,
  kError,
};

const std::vector<std::string> LogLevelNames = {
    "[TRACE]   ", "[DEBUG]   ", "[INFO]    ", "[WARNING] ", "[ERROR]   "};

const std::vector<std::string> LogLevelColors = {
    "\033[1;35m",        // Purple
    "\033[1;34m",        // Blue
    "\033[1;32m",        // Green
    "\033[1;38;5;208m",  // Orange
    "\033[1;31m",        // Red
    "",                  // Empty
};

enum OutputStream { kConsole, kFile, kBoth };
const std::vector<std::string> OutputStreamNames = {
    "CONSOLE", "FILE", "CONSOLE/FILE"};

class Logger {
 public:
  Logger(Logger&) = delete;
  void operator=(const Logger&) = delete;

  static Logger& GetInstance();

  static void SetLogLevel(const LogLevel& log_level);
  static void SetStream(const OutputStream& output);
  static void SetLogFile(const std::string& log_filename);
  static void EnableTimeStamp();
  static void DisableTimeStamp();
  static void EnableFileStamp();
  static void DisableFileStamp();

  template <typename... Args>
  static void Trace(int line_number, const std::string& file_name,
                    const Args&... args);

  template <typename... Args>
  static void Debug(int line_number, const std::string& file_name,
                    const Args&... args);

  template <typename... Args>
  static void Info(int line_number, const std::string& file_name,
                   const Args&... args);

  template <typename... Args>
  static void Warning(int line_number, const std::string& file_name,
                      const Args&... args);

  template <typename... Args>
  static void Error(int line_number, const std::string& file_name,
                    const Args&... args);

 private:
  Logger();

  LogLevel log_level_;
  OutputStream log_output_;
  std::string log_filename_;
  std::mutex log_mutex_;
  std::ofstream log_foutput_;
  bool time_stamp_;
  bool file_stamp_;

  template <typename... Args>
  void Log(LogLevel log_level, const Args&... args);
};

#define LOG_TRACE(...) (Logger::Trace(__LINE__, __FILE__, __VA_ARGS__))
#define LOG_INFO(...) (Logger::Info(__LINE__, __FILE__, __VA_ARGS__))
#define LOG_DEBUG(...) (Logger::Debug(__LINE__, __FILE__, __VA_ARGS__))
#define LOG_WARNING(...) (Logger::Warning(__LINE__, __FILE__, __VA_ARGS__))
#define LOG_ERROR(...) (Logger::Error(__LINE__, __FILE__, __VA_ARGS__))

#include "../src/Logger.tpp"  // Include the template implementation
#endif
