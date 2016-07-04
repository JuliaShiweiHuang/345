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
		
	} //if



	cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			cout << array[i][j];

	// 		string stringArray = array; // convert c-string to string
	// 		cout << stringArray.c_str(); // printed as a c-string 





	// array[200][60];
	// string stringArray = array; // convert c-string to string
	// cout << stringArray.c_str(); // printed as a c-string 



		}
	}

	cout << "*************************** END FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;





// cout << "************** BEGIN THIS IS ONLY MY STR() FUNCTION ******************" << endl;
	// for ( int row = 0; row < 2; row ++ ) {
	// 	string str(array[row]);
	// 	cout << str << endl;
	// }
	// for ( int row = 0; row < 2; row ++ ) {
	// 	cout << array[row] << endl;
	// }
	


// cout << "************** END THIS IS ONLY MY STR() FUNCTION ******************" << endl;

	// cout << "BEGIN TESTING ARRAY CONTENT" << endl;
	// cout << array[0][0];
	// cout << array[0][1];
	// cout << array[0][2];
	// cout << array[0][3];
	// cout << array[0][4];
	// cout << array[0][5];
	// cout << array[0][6];
	// cout << array[0][7];
	// cout << array[0][8];
	// cout << array[0][9];
	// cout << array[0][10];
	// cout << array[0][11];
	// cout << array[0][12];
	// cout << array[0][13];
	// cout << array[0][14];
	// cout << array[0][15];

	// cout << array[1][0];
	// cout << array[1][1];
	// cout << array[1][2];
	// cout << array[1][3];
	// cout << array[1][4];
	// cout << array[1][5];
	// cout << array[1][6];
	// cout << array[1][7];
	// cout << array[1][8];
	// cout << array[1][9];
	// cout << array[1][10];
	// cout << array[1][11];
	// cout << array[1][12];
	// cout << array[1][13];
	// cout << array[1][14];
	// cout << array[1][15];
	




	// cout << "END TESTING ARRAY CONTENT" << endl;





	// string str("This is \\cSar, hello!");
	// cout << str << endl;
	// istringstream iss(str);
	// do{
	// 	string sub;
	// 	iss >> sub;
	// 	cout << sub << endl;
	// } while (iss);








	// char indexArray[200][60];
	// for ( int i = 0; i < 200; i++ ) {
	// 	for ( int j = 0; j < 60; j++ ) {

	// 	}
	// // }
	
	// cout << "********************** BEGIN TESTING STATEMENT **********************" << endl;
	// cout << "number of row: " << row << endl;
	// cout << "number of col: " << col << endl;
	// cout << "********************** END TESTING STATEMENT **********************" << endl;


	// bool isSlash1 = checkSlash ( 'h' );
	// bool isSlash2 = checkSlash ( '\\');
	// cout << "***** BEGIN CHECKING SLASH *****" << endl;
	// cout << isSlash1 << endl;
	// cout << isSlash2 << endl;
	// cout << "***** END CHECKING SLASH *****" << endl;
	// cout << isSlash2 << endl;

file.close();

}

	// bool checkSlash ( char character) {
	// 	if ( character == '\\' ) {
	// 		return true;
	// 	}
	// 	else {
	// 		return false;
	// 	}
	// }

























	// cout << array[0][0];
	// cout << array[0][1];
	// cout << array[0][2];
	// cout << array[0][3];
	// cout << array[0][4];
	// cout << array[0][5];
	// cout << array[0][6];
	// cout << array[0][7];
	// cout << array[0][8];
	// cout << array[0][9];
	// cout << array[0][10];
	// cout << array[0][11];
	// cout << array[0][12];
	// cout << array[0][13];
	// cout << array[0][14];
	// cout << array[0][15];
	// cout << "Starting from here, it's first row" << endl;
	// cout << array[1][0];
	// cout << array[1][1];
	// cout << array[1][2];
	// cout << array[1][3];
	// cout << array[1][4];
	// cout << array[1][5];
	// cout << array[1][6];
	// cout << array[1][7];
	// cout << array[1][8];
	// cout << array[1][9];
	// cout << array[1][10];
	// cout << array[1][11];
	// cout << array[1][12];
	// cout << array[1][13];
	// cout << array[1][14];
	// cout << array[1][15];
	


