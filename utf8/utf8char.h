#ifndef UTF8_CHAR_H
#define UTF8_CHAR_H

#include <iostream>

struct UTF8err {              // exception
  const char *msg;
  UTF8err( const char *msg ) : msg( msg ) {}
};

struct character {
  union UTF8 {
    unsigned char ch;                        // character
    struct {                                 // types for 1st utf-8 byte
      unsigned char dt : 7;                  // data
      unsigned char ck : 1;                  // check
    } t1;
    struct {
      unsigned char dt : 5;                  // data
      unsigned char ck : 3;                  // check
    } t2;
    struct {
       // you figure it out
    } t3;
    struct {
      // you figure it out
    } t4;
    struct {                                 // type for extra utf-8 bytes
      // you figure it out
    } dt;
  } data[4];                                 // bytes in UTF-8 character
  unsigned int length;                       // number of bytes in UTF-8 character
};

wchar_t read(std::istream &, character &);   // read from istream into character

#endif
