#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {


	bool checkSlash ( char character) {
		if ( character == '\\' ) {
			return true;
		}
		else {
			return false;
		}
	}
}