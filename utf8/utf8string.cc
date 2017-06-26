#include "utf8string.h"
#include <cstring>
#include <cctype>
#include <sstream>
using namespace std;

utf8::string () {
 chars = NULL;
 length = 0;
 capacity = 0;
}//default constructor


void reserve(unsigned int n) {
 unsigned int cap = utf8::string.capacity;
 if (n > utf8::string.capacity) {
  while (n > cap) {
   cap = cap * 2; // enlarge the cap until it satisfy the capacity of utf8::string
  } 
  utf8::string.capacity = cap;
  character *newchar = new character[cap]; // allocate a new utf8::string
  memcpy(newchar, utf8::string.chars, cap * sizeof(character));//copy original string
  character * temp;
  temp = utf8::string.chars;
  utf8::string.chars = newchar;
  delete [] temp; //delete the original string
 } else {
 }
}



void push_back(character ch) {
 utf8::string.length += 1;
 if (utf8::string.capacity < UTF8::string.length) {
  reserve (utf8::string.length); // use reserve to enlarge the capacity if necessary
 }
 utf8::string.chars[utf8::string.length -1] = ch;
}


utf8::string operator+(utf8::string a, utf8::string b) {
  unsigned int len = a.capacity + b.capacity;
  character *mych = new character[len];
  for (unsigned int i = 0; i < a.length; ++i) {
   mych.[i] = a.chars[i];
  }
  for (unsigned int i = 0; i < b.length; ++i) {
   mych.[i + a.length] = b.chars[i];
  }
  return {
  mych;
  a.length + b.length;
  a.capacity + b.capacity;
 };
}
















