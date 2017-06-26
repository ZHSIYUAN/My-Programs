#include <cstdlib>          // atoi

void iterate( int i ) {
  volatile int bef = 0, aft = 0;  // prevent loop/recursion elimination
#if ! defined( RECURSION )
  for ( ;; ) {
    bef += 1;
    if ( i == 0 ) break;
    i -= 1;
    aft += 1;
  } // for
#else
  bef += 1;
  if ( i == 0 ) return;
  iterate( i - 1 );
  aft += 1;           // prevent tail recursion optimization
#endif
} // iterate

int main( int argc, char *argv[] ) {
  unsigned int times = 10000000;
  switch ( argc ) {
    case 2:
    times = atoi( argv[1] );
  } // switch

  iterate( times );
} // main
