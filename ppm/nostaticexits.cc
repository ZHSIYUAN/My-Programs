#include <cstdlib>          // atoi
#include <iostream>
using namespace std;

// volatile prevents dead-code removal
void do_work(int C1, int C2, int C3, int L1, int L2, volatile int L3 ) {
  int flag1 = 1;
  int flag2;
  int flag3;
  int i = 0; 
  while ((i < L1)&(flag1 == 1)) {
  // cout << "S1 i:" << i << endl;
   flag2 = 1;
   int j = 0;
   while ((j < L2)&(flag2 == 1)) {
    //cout << "S2 i:" << i << " j:" << j << endl;
    flag3 = 1;
    int k = 0;
    while ((k < L3)&(flag3 == 1)) {
     //cout << "S3 i:" << i << " j:" << j << " k:" << k << " : ";
     if (C1) {
      flag1 = 0;
      flag2 = 0;
      flag3 = 0;
     } else {
      //cout << "S4 i:" << i << " j:" << j << " k:" << k << " : ";
      if (C2) {
       //cout << "S8 i:" << i << endl;
       flag2 = 0;
       flag3 = 0;
      } else {
       //cout << "S5 i:" << i << " j:" << j << " k:" << k << " : ";
       if (C3) {
        //cout << "S7 i:" << i << " j:" << j << endl;
        flag3 = 0;
       } else {
        //cout << "S6 i:" << i << " j:" << j << " k:" << k << " : ";
       }
      }
     }
     k += 1;
    }
    if (flag3 == 0) {
     
    } else { 
     //cout << "S7 i:" << i << " j:" << j << endl;
    }
    j += 1;
   }
   if (flag2 == 0 && flag3 == 0) {
    
   } else {
    //cout << "S8 i:" << i << endl;
   }
   i += 1; 
  }
}


int main( int argc, char *argv[] ) {
  int times = 1, L1 = 10, L2 = 10, L3 = 10;
  if (argc == 5) {
   L3 = atoi( argv[4] );
   L2 = atoi( argv[3] );
   L1 = atoi( argv[2] );
   times = atoi( argv[1]);
  } else {
   cerr << "Usage: " << argv[0] << "times L1 L2 L3" << endl;
   exit( EXIT_FAILURE );
  }
  
 int i = 0;
 while (i < times) {
  int C1 = 0; 
  while (C1 < 2) {
   int C2 = 0;
   while (C2 < 2) {
    int C3 = 0;
    while (C3 < 2) {
     do_work( C1, C2, C3, L1, L2, L3 );
     //cout << endl;
     C3 += 1;
    } 
    C2 += 1;
   }
   C1 += 1;
  }
  i += 1;
 }
}

