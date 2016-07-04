// Last update: 10/05 19:42 Fully working version that read data from the file and store in an array;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool checkSlash (char );

int main () {

	ifstream file ( "shiwei.txt" );
	char character;
	char array[200][60];
	int row = 0, col = 0;

	// 2D Array initialization
	for ( int row = 0; row < 200; row ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}

	
	// From file to 2D array;
	if ( file.is_open() ) { //if I could locate my file;
		while ( file.get(character) ) {
			// cout << character;
			array[row][col] = character;
			col ++;
			if ( character == '\n' ) {
				row ++;
				col = 0;
			}
		}
		// cout << "******************* STARTING FROM HERE IS TO TEST array[row] *******************" << endl;
		// cout << array[1];

		// cout << "******************* END TEST array[row] *******************" << endl;
		
	} //if





	// print my 2D array
	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			cout << array[i][j];

			string stringArray = array; // convert c-string to string
			cout << stringArray.c_str(); // printed as a c-string 





	array[200][60];
	string stringArray = array; // convert c-string to string
	cout << stringArray.c_str(); // printed as a c-string 



		}
	}

	cout << "*************************** END FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;



// char myntcs[] = "some text";
// string mystring = myntcs;  // convert c-string to string
// cout << mystring;          // printed as a library string
// cout << mystring.c_str();  // printed as a c-string 






















}