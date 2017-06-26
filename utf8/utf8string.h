#ifndef UTF8_STRING_H
#define UTF8_STRING_H

#include <iostream>
#include "utf8char.h"

namespace utf8 {
  struct string {
    string();
    string(const string &);
    string(const char *);
    ~string();
    string & operator=(const string &);   // copy assignment operator
    void push_back( character ch );       // add one UTF-8 character to the end of the string
    void reserve( unsigned int n );       // if n > capacity, resize string to have enough space
                                          //   for n UTF-8 characters
    // data
    character * chars;                    // dynamically allocated array of UTF-8 characters
    unsigned int length;                  // # of UTF-8 characters currently in the chars array
    unsigned int capacity;                // maximum # of UTF-8 characters that chars can store
  };
}

#endif
