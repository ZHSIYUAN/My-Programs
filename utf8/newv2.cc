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
 myinfile->exceptions(ios_base::failbit);
 try {
  switch (argc) {
   case 2:
    try {
     myinfile = new ifstream(argv[1]); // open input file
     myinfile->exceptions(ios_base::failbit); // set exception
    } catch(ios_base::failure) {
     throw ios_base::failure("could not open input file"); //unable to open input file
    } // fall through
   case 1:
    break; // going to read in from standard input
   default:
    throw ios_base::failure("wrong number of arguments"); //incorrect numebr of arguments
  }
 } catch (ios_base::failure err) {
   cerr << err.what() << endl; // produce error message
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
    cout << showbase << hex << utf8code << " : valid value " << unicode << endl;
    } catch (UTF8err err) {
     wchar_t utf8code;
     utf8code = bitshift(mych);
     cout << showbase << hex << utf8code << " : " << err.msg << endl;
    }
   } 
 } catch (ios_base::failure) {} //end of file EOF
 if (myinfile != &cin) delete myinfile; 
}
