#include "Logger.hpp"

template <typename... Args>
void Logger::Trace(const Args&... args) {
  Log(LogLevel::kTrace, args...);
}

template <typename... Args>
void Logger::Debug(const Args&... args) {
  Log(LogLevel::kDebug, args...);
}

template <typename... Args>
void Logger::Info(const Args&... args) {
  Log(LogLevel::kInfo, args...);
}

template <typename... Args>
void Logger::Warning(const Args&... args) {
  Log(LogLevel::kWarning, args...);
}

template <typename... Args>
void Logger::Error(const Args&... args) {
  Log(LogLevel::kError, args...);
}

template <class Head, class... Tail>
void Printer(std::string& level_color, std::ostream& out, const Head& head,
             const Tail&... tail) {
  if (!level_color.empty()) out << level_color;

  out << head;
  ((out << ' ' << tail), ...);
  if (!level_color.empty()) out << RESET_COLOR;

  out << std::endl;
}

template <typename... Args>
void Logger::Log(LogLevel log_level, const Args&... args) {
  if (log_level >= log_level_) {
    std::scoped_lock lock(log_mutex_);
    std::string level_name = LogLevelNames[log_level];

    std::string level_color = LogLevelColors[log_level];
    if (log_output_ == OutputStream::kConsole ||
        log_output_ == OutputStream::kBoth) {
      Printer(level_color, std::cout, level_name, args...);
    }

    if (log_output_ == OutputStream::kFile ||
        log_output_ == OutputStream::kBoth) {
      level_color = "";
      Printer(level_color, log_foutput_, level_name, args...);
    }
  }
}