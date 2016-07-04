// Last update: 10/05 19:42 Fully working version that read data from the file and store in an array;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool checkSlash (char );

int main () {

	ifstream myFile ( "shiwei.txt" );
	char character;
	char array[200][60];
	int row = 0, col = 0;


	string emptyString = "";
	string stringInFile;



		if ( myFile.is_open() ) {	
			// myFile >> totalLineInFile; // the first line of the file will contain the number of other lines in the file;
			getline (myFile, emptyString); // Martin's note: read the rest of the empty first line;

/* The following part read the entire file and store the text in a single string */

			for ( int i = 0; i < 60; i++ ) {
					getline ( myFile, stringInFile ); // construct the text from .txt file into string;
					if ( stringInFile[stringInFile.length()-1] == ' ' ) { //if stringInFile has has a space by the end of the line; I am not adding a space in my string'stringInFile'
						emptyString = emptyString + stringInFile;
					}

					else {
						// if by the end of my file the user didn't contain " ";
						emptyString = emptyString + stringInFile + " "; // adding " " manually to make sure words in 'emptyString' are separated by a single space;
					}
			}//for

			cout << stringInFile << endl;

		}



	// cout << "*************************** BEGINING FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;
	// for ( int i = 0; i < 200; i++ ) {
	// 	for ( int j = 0; j < 60; j++ ) {
	// 		cout << array[i][j];

	// 		string stringArray = array; // convert c-string to string
	// 		cout << stringArray.c_str(); // printed as a c-string 





	// array[200][60];
	// string stringArray = array; // convert c-string to string
	// cout << stringArray.c_str(); // printed as a c-string 



	// 	}
	// }

	// cout << "*************************** END FROM HERE TO PRINT OUT MY 2D ARRAY ***************************" << endl;


	

myFile.close();

}
