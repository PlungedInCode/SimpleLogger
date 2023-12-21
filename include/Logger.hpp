#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <vector>

enum LogLevel {
  kTrace = 0,
  kDebug,
  kInfo,
  kWarning,
  kError,
};

const std::vector<std::string> LogLevelNames = {"TRACE", "DEBUG", "INFO",
                                                "WARNING", "ERROR"};

enum OutputStream { kConsole, kFile, kBoth };
const std::vector<std::string> OutputStreamNames = {"CONSOLE", "FILE",
                                                    "CONSOLE/FILE"};

class Logger {
 public:
  Logger(Logger&) = delete;
  void operator=(const Logger&) = delete;

  static Logger& GetInstance();

  static void SetLogLevel(const LogLevel& log_level);
  static void SetStream(const OutputStream& output);
  static void SetLogFile(const std::string& log_filename);

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

  template <typename... Args>
  static void Log(LogLevel log_level, const Args&... args);
};

#include "../src/Logger.tpp"  // Include the template implementation
#endif
