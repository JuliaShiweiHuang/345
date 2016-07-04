#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

	ifstream file ( "slash.txt" );
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
			array[row][col] = character;
			col ++;
			if ( character == '\n' ) {
				row ++;
				col = 0;
			}
		}
		
	} //if

	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;
	for ( int i = 0; i < 200; i++ ) { //(due to my 'if statement', this print array don't contain \(slash)
		for ( int j = 0; j < 60; j++ ) {
			cout << array[i][j];
		}
	}

	int identicalArray[200][60];
	for ( int row = 0; row < 200; row ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			identicalArray[row][col] = 0;
		}
	}

	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( array[i][j] == '\\' ) {
				identicalArray[i][j] = 1;
			}
		}
	}



	cout << "*************************** BEGINING FROM HERE TO PRINT OUT identicalArray ***************************" << endl;
	for ( int i = 0; i < 200; i++ ) { //(due to my 'if statement', this print array don't contain \(slash)
		for ( int j = 0; j < 60; j++ ) {
			cout << identicalArray[i][j];
		}
	}


	file.close();

}









	