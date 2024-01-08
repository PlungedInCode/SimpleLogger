#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <thread>

#include "Logger.hpp"

using std::istream;
using std::ostream;

struct Item {
  Item(const std::string& name, const std::string& description, float value,
    int count)
      : name_(name), description_(description), value_(value), count_(count) {}

  friend std::ostream& operator<<(std::ostream& os, const Item& a);

 private:
  std::string name_;
  std::string description_;
  float value_;
  int count_;
};

std::ostream& operator<<(std::ostream& os, const Item& a) {
  os << a.name_ << " - " << a.description_ << " = " << a.count_ << "*"
     << a.value_;
  return os;
}

class Date {
  int mo, da, yr;

 public:
  Date(int m, int d, int y) {
    mo = m;
    da = d;
    yr = y;
  }
  friend std::ostream& operator<<(std::ostream& os, const Date& dt);
};

std::ostream& operator<<(std::ostream& os, const Date& dt) {
  os << dt.mo << '/' << dt.da << '/' << dt.yr;
  return os;
}

class Complex {
 private:
  int real, imag;

 public:
  Complex(int r = 0, int i = 0) {
    real = r;
    imag = i;
  }
  friend ostream& operator<<(ostream& out, const Complex& c);
  friend istream& operator>>(istream& in, Complex& c);
};

ostream& operator<<(ostream& out, const Complex& c) {
  out << c.real;
  out << "+i" << c.imag;
  return out;
}

//----------------------------------------------------------------


void threadFunction(int n) { LOG_INFO("NUMBER N =", n, "--"); }

void threadTest(int n) {
  std::vector<std::thread> threads;

  for (int i = 0; i < n; i++) {
    threads.push_back(std::thread(threadFunction, i * n));
    if (i == n / 2) Logger::SetStream(kBoth);
  }

  for (int i = 0; i < n; i++) {
    threads[i].join();
  }
}

void testLogLevelAndStreams() {
  Logger::SetLogLevel(LogLevel::kTrace);

  Logger::SetStream(OutputStream::kConsole);
  LOG_TRACE("This is a trace message.");
  LOG_DEBUG("This is a debug message.");
  LOG_INFO("This is an info message.");

  Logger::SetStream(OutputStream::kFile);
  LOG_WARNING("This is a warning message to file.");
  LOG_ERROR("This is an error message to file.");
}

void testFileLoggingAndTimestamps() {
  Logger::SetLogFile("file_log.txt");
  Logger::EnableFileStamp();
  Logger::EnableTimeStamp();

  LOG_INFO("Logging with timestamps and file stamp.");

  Logger::DisableTimeStamp();
  LOG_DEBUG("Logging without timestamps.");

  Logger::DisableFileStamp();
  LOG_WARNING("Logging without file stamp.");

  Logger::SetLogFile("new_file_log.txt");
  LOG_ERROR("Logging to a different file.");
}

void testThreadedLogging() {
  Logger::SetStream(OutputStream::kBoth);

  const int numThreads = 5;
  std::thread threads[numThreads];

  for (int i = 0; i < numThreads; ++i) {
    threads[i] = std::thread([i]() {
      LOG_INFO("Thread ", i, ": Threaded log message.");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    });
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }
}

void testChangingLogLevel() {
  Logger::SetLogLevel(LogLevel::kWarning);

  LOG_INFO("This should not be logged.");
  LOG_WARNING("This should be logged.");

  Logger::SetLogLevel(LogLevel::kError);

  LOG_WARNING("This should not be logged.");
  LOG_ERROR("This should be logged.");
}

void testMultipleStreams() {
  Logger::SetLogLevel(LogLevel::kInfo);

  Logger::SetStream(OutputStream::kConsole);
  LOG_INFO("Message to console.");

  Logger::SetStream(OutputStream::kFile);
  LOG_INFO("Message to file.");

  Logger::SetStream(OutputStream::kBoth);
  LOG_INFO("Message to console and file.");
}

void testDisablingTimestamps() {
  Logger::EnableTimeStamp();

  LOG_INFO("Logging with timestamps.");

  Logger::DisableTimeStamp();

  LOG_WARNING("Logging without timestamps.");
}

void testDisablingFileStamp() {
  Logger::EnableFileStamp();

  LOG_INFO("Logging with file stamp.");

  Logger::DisableFileStamp();

  LOG_ERROR("Logging without file stamp.");
}

void testCombination() {
  Logger::SetLogLevel(LogLevel::kTrace);
  Logger::SetStream(OutputStream::kBoth);
  Logger::EnableTimeStamp();
  Logger::EnableFileStamp();

  LOG_TRACE("Combination test: Trace message.");
  LOG_DEBUG("Combination test: Debug message.");
  LOG_INFO("Combination test: Info message.");
  LOG_WARNING("Combination test: Warning message.");
  LOG_ERROR("Combination test: Error message.");
}

void testMultipleLogFile() {
  Logger::SetLogLevel(LogLevel::kTrace);

  Logger::SetLogFile("log_file1.txt");
  LOG_INFO("Logging to file 1.");

  Logger::SetLogFile("log_file2.txt");
  LOG_INFO("Logging to file 2.");
}

void runTest() {
  Logger::EnableFileClearing();
  // Logger::DisableFileClearing();
  testLogLevelAndStreams();
  testFileLoggingAndTimestamps();
  testThreadedLogging();
  testChangingLogLevel();
  testMultipleStreams();
  testDisablingTimestamps();
  testDisablingFileStamp();
  testCombination();
  testMultipleLogFile();
  threadTest(10);
}


#endif  // TEST_HPP
