// Last update: 10/05 19:42 Fully working version that read data from the file and store in an array;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

	char myntcs[] = "some text";
	string mystring = myntcs;  // convert c-string to string
	cout << mystring;          // printed as a library string
	cout << mystring.c_str();  // printed as a c-string 

}