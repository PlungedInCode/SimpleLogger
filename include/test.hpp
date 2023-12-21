#ifndef TEST_HPP
#define TEST_HPP
#include <iostream>
#include <string>
#include <thread>

using std::istream;
using std::ostream;

struct A {
  A(std::string name, std::string description, float value, int count)
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
  Logger::Debug(N, a, date, complex);
}

void threadFunction(int n) { Logger::Info(n); }

void threadTest() {
  std::thread threads[12];

  for (int i = 0; i < 10; i++) {
    threads[i] = std::thread(threadFunction, i);
    if (i == 5) Logger::SetStream(kBoth);
  }

  for (int i = 0; i < 10; i++) {
    threads[i].join();
  }
}

void runTest() {
  auto& logger = Logger::GetInstance();

  Logger::SetLogLevel(LogLevel::kTrace);

  logger.SetStream(OutputStream::kBoth);
  logger.Warning("1", 2, "3", "4", "5", 6, "7");

  logger.Warning("1", 2, "3", "4", "5", 6, "7");
  Logger::SetLogFile("log11.txt");

  Logger::SetStream(OutputStream::kFile);

  Logger::Error("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  logger.Warning("1", 2, "3", "4", "5", 6, "7");
  logger.Warning("1", 2, "3", "4", "5", 6, "7");
  logger.Warning("1", 2, "3", "4", "5", 6, "7");

  test(1);

  Logger::SetStream(OutputStream::kConsole);

  Logger::SetLogLevel(LogLevel::kTrace);

  test(2);

  Logger::SetStream(OutputStream::kFile);

  threadTest();
  Logger::SetStream(OutputStream::kBoth);
  Logger::Warning("1", 2, "3", "4", "5", 6, "7");
  Logger::SetLogFile("log11.txt");

  Logger::Error("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  Logger::Warning("1", 2, "3", "4", "5", 6, "7");
}

#endif  // TEST_HPP