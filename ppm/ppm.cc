#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct PpmImage {
  struct Pixel {
    unsigned char r, g, b;        // value for red, green, blue
  };
  unsigned int width, height, colourMax;  // image configuration
  Pixel **pixels;                 // matrix of pixels
};

void verticalflip(PpmImage &ppm) {
 PpmImage::Pixel **a = new PpmImage::Pixel *[ppm.height - 1];
 for (unsigned int i=0; i< ppm.height - 1; ++i) {
 a[i] = new PpmImage::Pixel [ppm.width -1];
 } //build a pixel to store data
 for (int i=0; i<(int)ppm.height; ++i) {
  a[(ppm.height-1) - i] = ppm.pixels[i];
 }
 for (int i=0; i<(int)ppm.height; ++i) {
  ppm.pixels[i] = a[i];
 }
 
}

void transpose(PpmImage &ppm) {
 PpmImage::Pixel **b =new PpmImage::Pixel *[ppm.width-1];
 for (unsigned int i=0; i<ppm.width; ++i) {
  b[i] = new PpmImage::Pixel [ppm.height - 1];
 }
 for (unsigned int i=0; i<ppm.height; ++i) {
  for (unsigned int j=0; j<ppm.width; ++j) {
  b[j][i] = ppm.pixels[i][j];
 }
 PpmImage::Pixel **d = ppm.pixels;
 ppm.pixels = b;
 delete [] d;
 }
}

void greyscale(PpmImage &ppm) {
 for (int i=0; i<(int)ppm.height; ++i) {
  for (int j=0; j<(int)ppm.width; ++j) {
   int aveg = ((int)ppm.pixels[i][j].r + (int)ppm.pixels[i][j].g + (int)ppm.pixels[i][j].b) / 3;
   ppm.pixels[i][j].r = (unsigned char)aveg;
   ppm.pixels[i][j].g = (unsigned char)aveg;
   ppm.pixels[i][j].b = (unsigned char)aveg;
  }
 }
}


int main(int argc, char *argv[]) {
 string header;
 unsigned int width, height, Max;
 cin >> header >> width >> height >> Max; // reads in header values
 if (cin.fail()) {                       
 cerr << "Errors with the file" << endl; // print error message if unable to read in
 exit(1); // exit with value 1
 }
 PpmImage myppm;
 myppm.width = width;
 myppm.height = height;
 myppm.colourMax = Max;
 myppm.pixels = NULL;
 cin.ignore();
 myppm.pixels = new PpmImage::Pixel *[height-1];// array index starts from 0
 unsigned int h = 0;
 while (h < height) {
 unsigned int w = 0;
 myppm.pixels[h] = new PpmImage::Pixel [width-1]; // array index starts from 0
 while (w < width) {
  PpmImage::Pixel mypixel; 
  cin.read(reinterpret_cast<char *>(&(mypixel.r)), 1);
  myppm.pixels[h][w].r =mypixel.r;  //mypixel.r;
  cin.read(reinterpret_cast<char *>(&(mypixel.g)), 1);
  myppm.pixels[h][w].g =mypixel.g;
  cin.read(reinterpret_cast<char *>(&(mypixel.b)), 1);
  myppm.pixels[h][w].b = mypixel.b;
  if (cin.eof()) break;
  if (cin.fail() ) {
   if (a > Max || b > Max || c > Max) {
    cerr << "Wrong Pixels" << endl;
    exit(1);
   }
   cerr << "Errors with the file" << endl;
   delete [] myppm.pixels;
   exit(1);
  }
  ++w;
  }
 ++h;
 }
 PpmImage &transppm = myppm;
 for (int index = 1; index < argc; ++index) {
  string flag = argv[index];
  if (flag == "-v")
  verticalflip(transppm);
  if (flag == "-t")
  transpose(transppm);
  if (flag == "-g")
  greyscale(transppm);
  if (flag != "-v" && flag != "-t" && flag != "-g") break;
  }
 cout<< header << " " << myppm.width << " " << myppm.height << " " << myppm.colourMax <<  endl; // formatted output
 for (unsigned int h = 0; h < myppm.height; ++h) {
  for (unsigned int w = 0; w < myppm.width; ++w) {
   PpmImage::Pixel mypixel;
   mypixel.r = myppm.pixels[h][w].r;
   mypixel.g = myppm.pixels[h][w].g;
   mypixel.b = myppm.pixels[h][w].b;
   cout.write(reinterpret_cast<char *>(&(mypixel.r)),1); // unformatted output
   cout.write(reinterpret_cast<char *>(&(mypixel.r)),1);
   cout.write(reinterpret_cast<char *>(&(mypixel.r)),1);  
  }
 }
 delete [] myppm.pixels;
} 




