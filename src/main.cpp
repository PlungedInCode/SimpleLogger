#include <iostream>

#include "../include/Logger.hpp"
#include "../include/test.hpp"

template <int N>
void test() {
  A a;
  Date date(12 + N, 21 / N, 2023 - N);
  Complex complex(3 * 2 * N,  2 * N);
  Logger::Debug(a, date, complex);
}

int main() {
  auto& logger = Logger::GetInstance();
  logger.Warning("1", 2, "3", "4", "5", 6, "7");
  Logger::SetLogLevel(LogLevel::kWarning);
  Logger::SetLogFile("log11.txt");
  Logger::SetStream(OutputStream::kBoth);
  Logger::Error("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  test<1>();
  Logger::SetLogLevel(LogLevel::kTrace);
  test<2>();
}