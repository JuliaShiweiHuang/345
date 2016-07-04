// Last update: 10/11 12:38 Fully working version 
// 1. Read data from the file and store in an array[200][60];
// 2. parallelArray knows exactly the location for '\'
// 3. Everything works ( but not thread 3 algorithm for now. )
// Question: 
// 1. What's the valid punctuation?
// 2. Would user input /uhappy!!

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int main () {

	ifstream file ( "file.txt" );
	char character;
	char array[5][21];
	int parallelArray[5][21];
	int row = 0, col = 0;

	// 2D Array initialization
	for ( int row = 0; row < 5; row ++ ) {
		for ( int col = 0; col < 21; col ++ ) {
			array[row][col] = ' ';
		}
	}


	// make a parallel array in order to identify the '/' location
	// parallelArray initialization;
	for ( int i = 0; i < 5; i ++ ) {
		for ( int j = 0; j < 21; j++ ) {
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
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 21; j++ ) {
			if ( array[i][j] == '\\' ) {
				parallelArray[i][j] = 1;
			}//if

		}//for
	}//for

// Making sure control sequence works;
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 21; j++ ) {
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
								if ( insideOneRow < 21  ) {
									array[i][j] = ' ';
									array[i][j+1] = ' ';
									array[i][insideOneRow] = toupper( array[i][insideOneRow] );
									insideOneRow ++;
								}
							}
						}//while;
					}//else if

					else { // array[i][j+1] == 'u'

						char tmpArray[0][21];
						int insideOneRow = j+2;
						bool noSpaceOrPunc = true;
						int countCharacter = 0;

						while ( noSpaceOrPunc ) {
							if ( array[i][insideOneRow] == ' ' || array[i][insideOneRow] == ',' || array[i][insideOneRow] == '!' || array[i][insideOneRow] == '.' ) {
								noSpaceOrPunc = false;
								array[i][j] = '_';
								array[i][j+countCharacter+1] = '_';
							}//if

							else {
								if ( insideOneRow < 21 ) {
									tmpArray[0][countCharacter] = array[i][insideOneRow];
									array[i][insideOneRow-1] = tmpArray[0][countCharacter];
									insideOneRow ++;
									countCharacter ++;
								}
							}//else

						}//while

					}//else
			}//if
		}//for
	}//for







	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;


	for ( int i = 0; i < 5; i++ ) { //(due to my 'if statement', this print array don't contain \(slash)
		for ( int j = 0; j < 21; j++ ) {
			cout << array[i][j];
		}
	}

	cout << "*************************** END FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;


// writing array content into file;
	ofstream myfile;
  	myfile.open ("fileshiwei.txt");
  	for ( int i = 0; i < 5; i++ ) {
  		for ( int j = 0; j < 21; j++ ) {
  			myfile << array[i][j];
  		}
  	}
  	myfile.close();

  	return 0;




	// ofstream myfile;
 //  	myfile.open ("answeranswer.txt");
  
 //  	for ( int i = 0; i < row; i ++ ) {
 //  		for ( int j = 0; j < 21; j++ ) {
 //  			if ( array[i][j] == 'a' || 'b' || 'c' || 'd' || 'e' || 'f' || 'g' || 'h' || 'i' || 'j' || 'k' || 'l' || 'm' || 'n' || 'o' || 'p' || 'q' || 'r' || 's' || 't' || 'u' || 'v' || 'w' || 'x' || 'y' || 'z' || 'A' || 'B' || 'C' || 'D' || 'E' || 'F' || 'G' || 'H' || 'I' || 'J' || 'K' || 'L' || 'M' || 'N' || 'O' || 'P' || 'Q' || 'R' || 'S' || 'T' || 'U' || 'V' || 'W' || 'X' || 'Y' || 'Z' || '_' || '.' || ',' || '!' ) {
 //  				myfile << array[i][j];
 //  			}
 //  			else {
 //  				myfile << " ";
 //  			}
 //  		}
 //  	}











} //main




