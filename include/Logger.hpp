#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <mutex>

#define RESET_COLOR "\033[0m"
#define NO_COLOR ""

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
    "\033[1;33m",        // Yellow
    "\033[1;34m",        // Blue
    "\033[1;32m",        // Green
    "\033[1;38;5;208m",  // Orange
    "\033[1;31m",        // Red
    "",                  // Empty
};

enum OutputStream { kConsole, kFile, kBoth };
const std::vector<std::string> OutputStreamNames = {"CONSOLE", "FILE",
                                                    "CONSOLE/FILE"}; // I don't think that i need this...

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

  template <typename... Args>
  static void Trace(const Args&... args);

  template <typename... Args>
  static void Debug(const Args&... args);

  template <typename... Args>
  static void Info(const Args&... args);

  template <typename... Args>
  static void Warning(const Args&... args);

  template <typename... Args>
  static void Error(const Args&... args);

 private:
  Logger();

  static LogLevel log_level_;
  static OutputStream log_output_;
  static std::string log_filename_;
  static std::mutex log_mutex_;
  static std::ofstream log_foutput_;
  static bool time_stamp_;

  template <typename... Args>
  static void Log(LogLevel log_level, const Args&... args);
};

#include "../src/Logger.tpp"  // Include the template implementation
#endif
