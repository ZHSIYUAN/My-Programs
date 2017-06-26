#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Node {
  string fileName;
  Node *link;
};

void processOneFile( istream &in, ostream &out, Node *flist, string prefixDir );
