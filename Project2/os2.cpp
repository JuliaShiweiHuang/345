// Last update: 10/10 19:58 Fully working version 
// 1. Read data from the file and store in an array[200][60];
// 2. parallelArray knows exactly the location for '\'

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

	ifstream file ( "control.txt" );
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


	// make a parallel array in order to identify the '/' location
	// parallelArray initialization;
	for ( int i = 0; i < 200; i ++ ) {
		for ( int j = 0; j < 60; j++ ) {
			parallelArray[i][j] = 0;
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
			}//if
		}//while

	} //if


	// Test to see parallelArray's '/' location;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( array[i][j] == '\\' ) {
				parallelArray[i][j] = 1;
			}//if
		}//for
	}//for

// Making sure control sequence works;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( parallelArray[i][j] == 1 ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j] = ' ';
						array[i][j+1] = ' ';
						array[i][j+2] = toupper( array[i][j+2] );
					}


// FIX TAKING OUT OF CONTROL SEQUENCE ISSUE

					else if ( array[i][j+1] == 'C' ) {
						bool noSpace = true;
						int insideOneRow = j+2;
						while ( noSpace ) {
							if ( array[i][insideOneRow] == ' ' ) {
								noSpace = false;
							}
							else {
								if ( insideOneRow < 60  ) {
									array[i][j] = ' ';
									array[i][j+1] = ' ';
									array[i][insideOneRow] = toupper( array[i][insideOneRow] );
									insideOneRow ++;
								}
							}
						}//while;
					}//else if

					else { // array[i][j+1] == 'u'

						cout << "hey" << endl;
// TO BE CONTINUED


						bool noSpaceOrPunc = true;
						int insideOneRow = j+2;
						int countCharacter = 0;
						char tmpArray[0][countCharacter];

						while ( noSpaceOrPunc ) {
							if ( array[i][insideOneRow] == ' ' || array[i][insideOneRow] == ',' || array[i][insideOneRow] == '!' || array[i][insideOneRow] == '.' ) {
								// array[i][insideOneRow-1] = '_';
								noSpaceOrPunc = false;
								countCharacter ++;
							}


							}

							else {
								tmpArray[0][i] = array[i][insideOneRow];
								
								array[i][insideOneRow]
								array[i][insideOneRow-2] = '_';
								array[i][insideOneRow-1] = array[i][insideOneRow];
								// to be continue...

							}
						}

//
//
//
						
						char tmpFirst = array[0][0];
						char tmpSecond = array[0][0];

						array[i][j] = '_';
						tmpFirst = array[i][j+2];
						tmpSecond = array[i][j+3];
						array[i][j+1] = tmpFirst;
						array[i][j+2] = tmpSecond;
						array[i][j+3] = '_';

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




