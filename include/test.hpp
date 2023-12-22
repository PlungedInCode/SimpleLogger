#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <thread>

#include "Logger.hpp"

using std::istream;
using std::ostream;

struct A {
  A(const std::string& name, const std::string& description, float value, int count)
      : name_(name), description_(description), value_(value), count_(count) {}

  friend std::ostream& operator<<(std::ostream& os, const A& a);

 private:
  std::string name_;
  std::string description_;
  float value_;
  int count_;
};

std::ostream& operator<<(std::ostream& os, const A& a) {
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

void test(int N) {
  A a("Name", "Discrption", 3.0, 4);
  Date date(12 + N, 21 / N, 2023 - N);
  Complex complex(3 * 2 * N, 2 * N);
  LOG_DEBUG(N, a, date, complex);
}

void threadFunction(int n) {LOG_INFO(n); }

void threadTest(int n) {
  std::thread threads[n];

  for (int i = 0; i < n; i++) {
    threads[i] = std::thread(threadFunction, i * n);
    if (i == n / 2) Logger::SetStream(kBoth);
  }

  for (int i = 0; i < n; i++) {
    threads[i].join();
  }
}

void runTest() {
  auto& logger = Logger::GetInstance();

  Logger::SetLogLevel(LogLevel::kTrace);

  logger.SetStream(OutputStream::kBoth);
  LOG_WARNING("1", 2, "3", "4", "5", 6, "7");

  LOG_TRACE("1", 2, "3", "4", "5", 6, "7");
  LOG_ERROR("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);

  Logger::SetLogFile("log1.txt");

  Logger::SetStream(OutputStream::kFile);
  LOG_ERROR("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  LOG_WARNING("1", 2, "3", "4", "5", 6, "7");


  test(1);

  Logger::SetStream(OutputStream::kConsole);

  Logger::SetLogLevel(LogLevel::kTrace);

  test(2);

  Logger::SetStream(OutputStream::kFile);

  Logger::DisableFileStamp();
  Logger::DisableTimeStamp();
  threadTest(14);

  Logger::SetStream(OutputStream::kBoth);
  LOG_WARNING("1", 2, "3", "4", "5", 6, "7");
  Logger::SetLogFile("log.txt");

  Logger::EnableFileStamp();
  Logger::EnableTimeStamp();
  LOG_WARNING("1", 2, "3", "4", "5", 6, "7");  
  LOG_ERROR("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  threadTest(13);
}

#endif  // TEST_HPP