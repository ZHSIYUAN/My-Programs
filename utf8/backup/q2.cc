#include "utf8char.h"
using namespace std;

wchar_t bitshift(character & ch) {
 wchar_t mywchar;
 if (ch.length == 1) {
  mywchar = ch.data[0].ch;
 } else if (ch.length == 2) {
  mywchar = (ch.data[0].ch << 8) + ch.data[1].ch;
 } else if (ch.length == 3) {
  mywchar = (ch.data[0].ch << 16) + (ch.data[1].ch << 8)
            + ch.data[2].ch;
 } else {
  mywchar = (ch.data[0].ch << 24) + (ch.data[1].ch << 16)
            + (ch.data[2].ch << 8) + ch.data[3].ch;
 }
 return mywchar;
}


int main( int argc, char *argv[] ) {
 istream *myinfile = &cin; // set cin to use exception
 try {
  switch (argc) {
   case 2:
      myinfile = new ifstream(argv[1]); // open input file
      if (myinfile->fail()) {
       string c = "could not open input file";
       throw c;
      }  // set exception  // fall through
   case 1:
    break; // going to read in from standard input
   default:
    {
    string a = "wrong number of arguments";
    throw a;
    } //incorrect numebr of arguments
  }
 } catch (string b) {
   cerr << b << endl; // produce error message
   cerr << "Usage: " << argv[0] << " " << "[ infile-file ]" << endl; // produce correct format
   exit(EXIT_FAILURE); // terminate 
 }
 
 try {
 character mych;
   for ( ;; ) {
    try {
     wchar_t unicode = read(*myinfile, mych);
     wchar_t utf8code;
     utf8code = bitshift(mych);
     if ((utf8code >= 0x00) && (utf8code <= 0x0f)) {
      cout << noshowbase << hex << "0x" << "0" << utf8code
      << " : valid value " << "0x" << unicode <<endl;
     } else {
      cout << showbase << hex << utf8code 
      << " : valid value " << unicode << endl;
     }
    } catch (UTF8err err) {
     wchar_t utf8code;
     utf8code = bitshift(mych);
      cout << showbase << hex << utf8code << " : " << err.msg << endl;
    } catch (int k) {
     throw k;
    }
   }
 } catch (int i) {} //end of file EOF
 if (myinfile != &cin) delete myinfile; 
}
