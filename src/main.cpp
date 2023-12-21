#include <fstream>
#include <iostream>

#include "Logger.hpp"
#include "test.hpp"

void PrinterCH(std::ostream& out, std::string text) {
  out << text << std::endl;
}

int main() { runTest(); }