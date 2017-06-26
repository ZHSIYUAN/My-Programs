#include <iostream>
using namespace std;

struct Complex {
 int c;
 int d;
 Complex add(Complex a) {
  return {c + a.c, d + a.d};
  }
}

Complex c;
c = { 2, 3 };
Complex d;
d = { 3, 4 };

Complex sum = c.add(d);
cout << sum.c << " " << sum.d << endl;

