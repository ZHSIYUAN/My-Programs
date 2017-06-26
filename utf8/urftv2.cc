#include <string>
#include <utility>
#include <algorithm>

namespace utf8 {
 string ::string() {
  length = capacity = 0;
  chars = NULL;
 }

 string::string(const string & other) {
  capacity = length = other.length;
  chars = new character[capacity];
  memcpy(chars, other.chars, length*sizeof(character));
 }
 
 string ::~string() {
  delete[] chars;
 }

 string & string::operator=(const string & other) {
  using std::swap;
  string copy = other;
  swap(chars, copy.chars);
  swap(length, copy.length);
  swap(capacity, copy.capacity);
  return *this;
 }
 
 string::string(const char * other) {
  capacity = length = strlen(other);
  chars = new character[capacity];
  for(unsigned int i = 0; i < length; ++i) {
   chars[i].data[0].ch = other[i];
   chars[i].length = 1;
  }
 }
 
 void string::push_back(character utf8) {
  if(n > capacity) {
   character * old = chars;
   capacity = n;
   chars = new character[capacity];
   memcpy(chars, old, length*sizeof(character));
   delete[] old;
  }
 }
}




utf8::sring operator+(const utf8::string & s1, const utf8::string & s2) {
 utf8::string ret;
 ret.reserve(s1.length + s2.length);
 memcpy(ret.chars, s1.chars, s1.chars,s1.length* sizeof(character));
 memcpy(&ret.chars[s1.length], s2.chars, s2.length * sizeof(character));
 ret.length = s1.length + s2.length;
 return ret;
}


std::ostream & operator<<(std::ostream & out, const utf8::string & s) {
 for(unsigned int i=0; i < s.length; ++i) {
  out.write((char *) & s.chars[i].data, schar[i].length);
 }
 return out;
}


std::istream & operator>>(std::istream & in, utf8::string & s) {
 using namespace utf8;
 s.length = 0;
 character utf8;
 
 // suck up all of the whitespace
 for(;;) {
  read(in,utf8);
  if(in.fail()) {
   return in;
  }
 // assume skipws
  if(utf8.length != 1 || !std::isspace(utf8.data[0].ch)) {
   //first non-whitespace character
   s.push_buck(utf8);
   break;
  }
 }
 
 //read until next whitespace
 for (;;) {
  read(in,utf8);
  if(in.fail()) {
   return in;
  }
  if (utf8.length == 1 && std::isspace(utf8.data[0].ch)) {
   return in;
  }
  s.push_buck(utf8);
 }

 return in;
}





 
 






