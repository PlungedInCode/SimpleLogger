#include "Logger.hpp"

Logger::Logger()
    : log_level_(LogLevel::kInfo),
      log_output_(OutputStream::kConsole),
      log_filename_("log.txt"),
      log_mutex_(),
      time_stamp_(true),
      file_stamp_(true) {}

Logger& Logger::GetInstance() {
  static Logger instance;
  return instance;
}

void Logger::SetLogLevel(const LogLevel& log_level) {
  GetInstance().log_level_ = log_level;
}

void Logger::SetStream(const OutputStream& output) {
  auto& logger = GetInstance();
  {
    std::scoped_lock lock(logger.log_mutex_);
    logger.log_output_ = output;
    if (logger.log_output_ == kBoth || logger.log_output_ == kFile) {
      if (!logger.log_foutput_.is_open()) {
        logger.log_foutput_.open(logger.log_filename_, std::ios::app);
      }
    }
    if (logger.log_output_ == kConsole && logger.log_foutput_.is_open()) {
      logger.log_foutput_.close();
    }
  }
}

void Logger::SetLogFile(const std::string& log_filename) {
  auto& logger = GetInstance();
  if (logger.log_foutput_.is_open()) {
    logger.log_foutput_.close();
  }
  logger.log_filename_ = log_filename;
  if (logger.log_output_ == kBoth || logger.log_output_ == kFile) {
    logger.log_foutput_.open(logger.log_filename_, std::ios::app);
  }
}

void Logger::EnableTimeStamp() { GetInstance().time_stamp_ = true; }

void Logger::DisableTimeStamp() { GetInstance().time_stamp_ = false; }

void Logger::EnableFileStamp() { GetInstance().file_stamp_ = true; }

void Logger::DisableFileStamp() { GetInstance().file_stamp_ = false; }