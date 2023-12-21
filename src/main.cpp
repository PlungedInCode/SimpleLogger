#include <iostream>


#include "Logger.hpp"
#include "test.hpp"

int main() {
  // auto& logger = Logger::GetInstance();
  // logger.Warning("1", 2, "3", "4", "5", 6, "7");
  // Logger::SetLogLevel(LogLevel::kWarning);
  // Logger::SetLogFile("log11.txt");
  // Logger::SetStream(OutputStream::kBoth);
  // Logger::Error("Hello", ",", "World", "!", "2", "*", 2.4, "=", 4.8);
  // test(1);
  // Logger::SetLogLevel(LogLevel::kTrace);
  // test(2);

  threadTest();
}