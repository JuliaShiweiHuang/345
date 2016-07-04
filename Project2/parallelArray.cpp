// Last update: 10/10 19:58 Fully working version 
// 1. Read data from the file and store in an array[200][60];
// 2. parallelArray knows exactly the location for '\'

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

	ifstream file ( "shiwei.txt" );
	char character;
	char array[200][60];
	int parallelArray[200][60];
	int row = 0, col = 0;

	// 2D Array initialization
	for ( int row = 0; row < 200; row ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}


	cout << "1. see whether here is some input" << endl;
	// make a parallel array in order to identify the '/' location
	// parallelArray initialization;
	for ( int i = 0; i < 200; i ++ ) {
		for ( int j = 0; j < 60; j++ ) {
			parallelArray[i][j] = 0;
		}
	}

	cout << "2. see whether here is some input" << endl;

	// From file to 2D array;
	if ( file.is_open() ) { //if I could locate my file;
		while ( file.get(character) ) {
			array[row][col] = character;
			col ++;
			if ( character == '\n' ) {
				row ++;
				col = 0;
			}//if
		}//while

	} //if


	cout << "3. see whether here is some input" << endl;
	// Test to see parallelArray's '/' location;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( array[i][j] == '\\' ) {
				parallelArray[i][j] = 1;
			}//if
		}//for
	}//for


	cout << "4. see whether here is some input" << endl;

	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY PARALLEL ARRAY ***************************" << endl;
	// for ( int i = 0; i < 200; i++ ) { //(due to my 'if statement', this print array don't contain \(slash)
	// 	for ( int j = 0; j < 60; j++ ) {
	// 		cout << parallelArray[i][j];
	// 	}
	// }
	cout << "*************************** END FROM HERE TO PRINT OUT MY PARALLEL ARRAYw ***************************" << endl;
	cout << "line73";
cout << "line74";
	for ( int i = 0; i < 200; i++ ) {
		cout << "line76";
		for ( int j = 0; j < 60; j++ ) {
			if ( parallelArray[i][j] == 1 ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j+2] = toupper( array[i][j+2] );
					}
cout << "line83";
					if ( array[i][j+1] == 'C' ) {
						//function;
						
						bool noSpace = true;
						while ( noSpace ) {
							
							for ( int insideOneRow = j+2; insideOneRow < 60 - j; insideOneRow++ ) {
								if ( array[i][insideOneRow] == ' ' ) {
									noSpace = false;
								}
								else {
									array[i][insideOneRow] = toupper ( array[i][insideOneRow] );
									noSpace = true;
								}
							}
						}
						cout << "line99";

					}

					else { // array[i][j+1] == 'u'
						//function;
					}
			}
		}//for
	}//for






	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;
	for ( int i = 0; i < 200; i++ ) { //(due to my 'if statement', this print array don't contain \(slash)
		for ( int j = 0; j < 60; j++ ) {
			cout << array[i][j];
		}
	}

	cout << "*************************** END FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;












} //main




