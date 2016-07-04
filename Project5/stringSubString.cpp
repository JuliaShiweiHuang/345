// string::substr
#include <iostream>
#include <string>

using namespace std;

int main ()
{
  string str="We think in generalities, but we live in details.";
                                           // (quoting Alfred N. Whitehead)
  string str2 = str.substr (3,7);     // "think"
  cout << "this is str2: " << str2 << endl;
  return 0;
}