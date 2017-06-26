#ifndef PRINTER_H
#define PRINTER_H

class Printer {
  public:
    enum Kind { Mashed, Fried, Umpire, Player };
    Printer( unsigned int players );
    ~Printer();
    void print( Kind kind, unsigned int state, unsigned int id = 0, unsigned int player = 0 );
};

#endif
