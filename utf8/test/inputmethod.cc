#include <iostream>
#include <fstream>
using namespace std;

int main() {
 ofstream outfile("myinput7");
 unsigned char utf8bytes[] = {
  0xe0,
  0x80,
  0x80,
  0xd7,
  0x81,
  0x24
};
 outfile.write((char *)utf8bytes, sizeof(utf8bytes));
}



