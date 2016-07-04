/* toupper example */
#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main () {



  char myTestCharacter = 'c';
  
  char myTest = toupper(myTestCharacter);
  cout << myTest << endl;

  cout << "******** TESTING ANOTHER ********" << endl;

  char array[60][1];
  array[0][0] = 'z';
  char another = toupper( array[0][0] );
  cout << "test another case: " << another << endl;



}

