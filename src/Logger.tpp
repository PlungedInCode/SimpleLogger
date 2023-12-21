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
void Printer(const Head& head, const Tail&... tail) {
  std::cout << head;
  ((std::cout << ' ' << tail), ...);
  std::cout << std::endl;
}

template <typename... Args>
void Logger::Log(LogLevel log_level, const Args&... args) {
  if (log_level >= log_level_) {
    std::string level_name = "[" + LogLevelNames[log_level] + "] -";
    Printer(level_name, args...);
  }
}