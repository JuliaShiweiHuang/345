// Last update: 10/13 13:54 p.m Fully working version 
// 1. Read data from the file and store in an array[200][60];
// 3. Everything works ( but not thread 3 algorithm for now. )

#include <iostream>     // std::cout, std::endl
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

	ifstream file ( "macInput.txt" );
	char character;
	char array[200][60];
	int row = 0, col = 0;

cout << "1" << endl;
	

cout << "2" << endl;
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
// 2D Array initialization
	for ( int i = 0; i < row; i ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}

cout << "3" << endl;


// Making sure control sequence works;
	for ( int i = 0; i < row; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( array[i][j] == '\\' ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j] = ' ';
						array[i][j+1] = ' ';
						array[i][j+2] = toupper( array[i][j+2] );
					}//if

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

						char tmpArray[0][60];
						int insideOneRow = j+2;
						bool noSpaceOrPunc = true;
						int countCharacter = 0;

						while ( noSpaceOrPunc ) {
							if ( array[i][insideOneRow] == ' ' || array[i][insideOneRow] == ',' || array[i][insideOneRow] == '!' || array[i][insideOneRow] == '.' || array[i][insideOneRow] == '\n' ) {
								noSpaceOrPunc = false;
								array[i][j] = '_';
								array[i][j+countCharacter+1] = '_';
							}//if

							else {
								if ( insideOneRow < 60 ) {
									tmpArray[0][countCharacter] = array[i][insideOneRow];
									array[i][insideOneRow-1] = tmpArray[0][countCharacter];
									insideOneRow ++;
									countCharacter ++;
								}
							}//else

						}//while

					}//else
			}//if
			cout << array[i][j];
		}//for
	}//for


cout << "4" << endl;
// writing from array to .txt file;
	ofstream myfile;
  	myfile.open ("macOutputss.txt");
  	float space = 5.5/2.5;
	for ( int i = 0; i < row; i++ ) {
	  	for ( int j = 0; j < 60; j++ ) {
	  		if ( array[i][j] != ' ' ) { 
	  			myfile << array[i][j];
	  		}//if
	  		else { //only adding manmaid space if word and space are saparated by 1 space ( rather than 2 spaces or 3 spaces outputFileShiwei2);
	  			if ( ( array[i][j] == ' ' ) && ( array[i][j+1] != ' ' ) ) {
	  				myfile << setw(space);
	  			}//if
	  		}//else
	  	}//for
	}//for

cout << "5" << endl;
  	myfile.close();

  	return 0;

} //main




