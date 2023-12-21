#include <iostream>
#include <string>

using std::istream;
using std::ostream;

struct A {
  A() {
    name = "A";
    description = "description";
    value = 3.0;
    count = 1;
  }

  friend std::ostream& operator<<(std::ostream& os, const A& a);

 private:
  std::string name;
  std::string description;
  float value;
  int count;
};

std::ostream& operator<<(std::ostream& os, const A& a) {
  os << a.name << " - " << a.description << " = " << a.count << "*" << a.value;
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