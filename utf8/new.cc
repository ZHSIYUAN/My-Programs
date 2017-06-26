#include <cstdlib>        // atoi

void alloc( unsigned int size, unsigned int times ) {
  for ( unsigned int i = 0; i < times; i += 1 ) {
#ifdef DYN
    volatile int *arr = new int[size];
    arr[0] = 5;
    delete [] arr;
#else
    volatile int arr[size]; // ignore volatile, prevents elimination of declaration & assignment
    arr[0] = 5;
#endif
  } // for
} // alloc

int main( int argc, char *argv[] ) {
  int times = 100000000;
  switch ( argc ) {
    case 2:
     times = atoi( argv[1] );
  } // switch

  alloc( 10, times );

  volatile int *arr = 0;    // ignore volatile, prevents elimination of declaration & deallocation
  delete arr;
} // main
