#include "Logger.hpp"
// #include "../include/Logger.hpp"

// Initializing Logger's static members
LogLevel Logger::log_level_ = LogLevel::kInfo;
OutputStream Logger::log_output_ = OutputStream::kConsole;
std::string Logger::log_filename_ = "log.txt";
std::mutex Logger::log_mutex_;
std::ofstream Logger::log_foutput_;
bool Logger::time_stamp_ = true;

Logger::Logger() {}

Logger& Logger::GetInstance() {
  static Logger instance;
  return instance;
}

void Logger::SetLogLevel(const LogLevel& log_level) { log_level_ = log_level; }

void Logger::SetStream(const OutputStream& output) {
  std::scoped_lock lock(log_mutex_);
  log_output_ = output;
  if (log_output_ == kBoth || log_output_ == kFile) {
    if (!log_foutput_.is_open()) {
      log_foutput_.open(log_filename_, std::ios::app);
    }
  }
  if (log_output_ == kConsole)
    if (log_foutput_.is_open()) log_foutput_.close();
}

void Logger::SetLogFile(const std::string& log_filename) {
  log_filename_ = log_filename;
  if (log_foutput_.is_open()) {
    log_foutput_.close();
    log_foutput_.open(log_filename_, std::ios::app);
    // SetStream(log_output_);
  }
}

void Logger::EnableTimeStamp() { time_stamp_ = true; }

void Logger::DisableTimeStamp() { time_stamp_ = false; }