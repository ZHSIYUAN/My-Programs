#ifndef POTATO_H
#define POTATO_H

class Potato {
    // YOU ADD MEMBERS
  public:
    struct Expire {};                // raise when timer expires
    Potato( Printer &prt );
    virtual void reset() = 0;        // must be defined in derived class
    virtual void countdown();
};

class Mashed : public Potato {
    // YOU ADD MEMBERS
  public:
    Mashed( Printer &prt, unsigned int maxTicks = 10 );
    void reset();
    void countdown();
};

class Fried : public Potato {
    // YOU ADD MEMBERS
  public:
    Fried( Printer &prt, unsigned int maxTicks = 10 );
    void reset();
    void countdown();
};

#endif
