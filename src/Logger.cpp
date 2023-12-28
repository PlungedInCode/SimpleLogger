#include "Logger.hpp"

Logger::Logger()
    : log_level_(LogLevel::kInfo),
      log_output_(OutputStream::kConsole),
      log_filename_("log.txt"),
      log_mutex_(),
      time_stamp_(false),
      file_stamp_(false),
      file_clearing_(false) {}

Logger& Logger::GetInstance() {
  static Logger instance;
  return instance;
}

void Logger::SetLogLevel(const LogLevel& log_level) {
  GetInstance().log_level_ = log_level;
}

void Logger::OpenFile() {
  auto mode = std::ios::app;
  if (file_clearing_) {
    mode = std::ios::trunc;
  }
  log_foutput_.open(log_filename_, mode);
}

void Logger::SetStream(const OutputStream& output) {
  auto& logger = GetInstance();
  {
    std::scoped_lock lock(logger.log_mutex_);
    logger.log_output_ = output;
    if (logger.log_output_ == kBoth || logger.log_output_ == kFile) {
      if (!logger.log_foutput_.is_open()) {
        // logger.log_foutput_.open(logger.log_filename_, std::ios::app);
        logger.OpenFile();
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
    logger.OpenFile();
    // if (logger.file_clearing_)
    //   logger.log_foutput_.open(logger.log_filename_, std::ios::app);
    // else
    //   logger.log_foutput_.open(logger.log_filename_, std::ios::app);
  }
}

void Logger::EnableTimeStamp() { GetInstance().time_stamp_ = true; }

void Logger::DisableTimeStamp() { GetInstance().time_stamp_ = false; }

void Logger::EnableFileStamp() { GetInstance().file_stamp_ = true; }

void Logger::DisableFileStamp() { GetInstance().file_stamp_ = false; }

void Logger::EnableFileClearing() { GetInstance().file_clearing_ = true; }

void Logger::DisableFileClearing() { GetInstance().file_clearing_ = false; }
