#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <iomanip>
#include <cmath> 


using namespace std;	

int main () {


		ifstream myFile ("macOutputs.txt");

		int totalLineInFile;
		string stringInFile;

		string emptyString = ""; 

		if ( myFile.is_open() ) {	
			getline (myFile, emptyString); // Martin's note: read the rest of the empty first line;

			for ( int i = 0; i < 10; i++ ) {
					getline ( myFile, stringInFile ); // construct the text from .txt file into string;
					if ( stringInFile[stringInFile.length()-1] == ' ' ) { //if stringInFile has has a space by the end of the line; I am not adding a space in my string'stringInFile'
						emptyString = emptyString + stringInFile;
					}

					else {
						// if by the end of my file the user didn't contain " ";
						emptyString = emptyString + stringInFile + " "; // adding " " manually to make sure words in 'emptyString' are separated by a single space;
					}
			}//for
			
cout <<"string: " << endl;
cout << emptyString << endl;
		}//if file is open;
		else {
			cout << "sorry. Cannot location your file." << endl;
		}

		return 0;


}











