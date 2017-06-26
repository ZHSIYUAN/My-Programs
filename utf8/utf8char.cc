#include "utf8char.h"

wchar_t read(std::istream & infile, character & ch) {
 
 infile.read(reinterpret_cast<char *>(&(ch.data[0].ch)), sizeof(unsigned char));
  //array address, determine the size of readin char
 if (ch.data[0].t1.ck == 0) {
     ch.length = 1; // use check bits to determine number of bytes to read
 } else if (ch.data[0].t2.ck == 6) {
     ch.length = 2;
     infile.read(reinterpret_cast<char *>(&(ch.data[1].ch)), 
                sizeof(unsigned char));
     if(infile.eof()) {
      ch.length = 1; // change length
      throw UTF8err("invalid missing bytes"); // throw missing bytes
      } 
     if (ch.data[1].dt.ck != 2) {
       throw UTF8err("invalid padding");
     }
 } else if (ch.data[0].t3.ck == 14) {
     ch.length = 3;
     for (int i = 1; i < 3; ++i) {
      infile.read(reinterpret_cast<char *>(&(ch.data[i].ch)),
                  sizeof(unsigned char));
      if(infile.eof()) {
         ch.length = i; // change length
         throw UTF8err("invalid missing bytes"); // throw missing bytes
         break;
        }
      if (ch.data[i].dt.ck != 2) {
         ch.length = i + 1;
         throw UTF8err("invalid padding");
         break;
      }
     }
 } else if (ch.data[0].t4.ck == 30) {
     ch.length = 4;
     for (int i = 1; i < 4; ++i) {
      infile.read(reinterpret_cast<char *>(&(ch.data[i].ch)),
                  sizeof(unsigned char));
      if(infile.eof()) {
        ch.length = i; // change length
        throw UTF8err("invalid missing bytes"); // throw missing bytes
        break;  
      }
     if (ch.data[i].dt.ck != 2) {
        ch.length = i + 1;
        throw UTF8err("invalid padding");
        break;
     }
     }
 } else {
   ch.length = 1;
    throw UTF8err("invalid length");//throw a error of invalid length
 }
  //check invalid padding 
 if (ch.length == 2) {
  if (ch.data[1].dt.ck != 2) throw UTF8err("invalid padding");
 } else if (ch.length == 3) {
  if (ch.data[1].dt.ck != 2) throw UTF8err("invalid padding");
  if (ch.data[2].dt.ck != 2) throw UTF8err("invalid padding");
 } else if (ch.length == 1) {
  
 } else {
  if (ch.data[1].dt.ck != 2) throw UTF8err("invalid padding");
  if (ch.data[2].dt.ck != 2) throw UTF8err("invalid padding");
  if (ch.data[3].dt.ck != 2) throw UTF8err("invalid padding");
 }
 wchar_t a; 
 if (ch.length == 1) {
  a = ch.data[0].t1.dt;
  if ((a < 0x00) || (a > 0x7f)) {
   throw UTF8err("invalid range");
  }
 } else if (ch.length == 2) {
  a = (ch.data[0].t2.dt << 6) + ch.data[1].dt.dt;
  if ((a < 0x80) || (a > 0x7ff)) {
   throw UTF8err("invalid range");
  } // check for invalid range
 } else if (ch.length == 3) {
  a = (ch.data[0].t3.dt << 12) + (ch.data[1].dt.dt << 6) + ch.data[2].dt.dt;
  if ((a < 0x800) || (a > 0xffff)) {
   throw UTF8err("invalid range");
  } // check for invalid range
 } else {
  a = (ch.data[0].t4.dt << 18) + (ch.data[1].dt.dt << 12) + 
      (ch.data[2].dt.dt << 6) + ch.data[3].dt.dt;
  if ((a < 0x10000) || (a > 0x10ffff)) {
   throw UTF8err("invalid range");
  } // check for invalid range
 }
 return a;
}



