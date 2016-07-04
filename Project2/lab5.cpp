// THIS PROGRAM COULD COMPILE
// HOWEVER, COUPLE NOTES:
// 1. NEED TO TEST MY FIND LARGEST POINT Function
// 2. Still need to find a way to store string.


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>      /* printf */
#include <math.h>

using namespace std;



int StringMatchingBF (string , string );

// Takes two strings as input and return the index of the first location in the first string input;
int StringMatchingBF ( string str1, string str2 ) {
	for ( int i = 0; i < str1.length() - str2.length(); i++ ) {
		int j = 0;
		while (( j < str2.length() ) && ( str1[i+j] == str2[j] )) {
			j++;
		}

		if ( j == str2.length() ) {
			return i;
		}
	}
	return -1;
}


class point2D {
public:
	int xCoordinate, yCoordinate;
	//write a constructor that takes two integers as input and uses them to initialize the xCoordinate and yCoordinate of the point;
	point2D ( int x, int y ) { xCoordinate = x; yCoordinate = y;}; 
	string toString ();

};

// input: a toString function that takes no input;
// output: a string representing the point;
// for example, toString should return the string "(11, 5)" if my x coordinate of the point is 11, and the y coordinate of the point is 5;
string point2D :: toString () {
	string intToStringFirstValue, intToStringSecondValue; //to store converted results;
	ostringstream convertXCoordinate, convertYCoordinate;
	convertXCoordinate << xCoordinate;
	convertYCoordinate << yCoordinate;

	intToStringFirstValue = convertXCoordinate.str();
	intToStringSecondValue = convertYCoordinate.str(); 
	return "(" + intToStringFirstValue + "," + intToStringSecondValue + ")";
}


// A function closestPairBF that takes as input an array of pointers to pointer2D, its size, and two other integers passed by reference (that will be used to return the indices of the closest points);
// Function is not returning anything ( apart from the two indices passed by reference );
// The function should implement the function seen in class;
void ClosestPairBF ( point2D **arrayOfPointers, int size, int &locationForPt1, int &locationForPt2 ) {

	int minDistance = ((arrayOfPointers[0] -> yCoordinate - arrayOfPointers[1] -> yCoordinate) * (arrayOfPointers[0] -> yCoordinate - arrayOfPointers[1] -> yCoordinate)) +
					  ((arrayOfPointers[0] -> xCoordinate - arrayOfPointers[1] -> xCoordinate) * (arrayOfPointers[0] -> xCoordinate - arrayOfPointers[1] -> xCoordinate));
	locationForPt1 = 0; 
	locationForPt2 = 1;
	//point2D minIndices (0,1);

	for ( int i = 0; i <= size - 2; i++ ) {
		for ( int j = i+1; j <= size - 1; j++ ) {

			if ( minDistance > ((arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate) * (arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate)) +
			   ((arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate) * (arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate)))
			{	
				minDistance = ((arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate) * (arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate)) +
					          ((arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate) * (arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate));
				locationForPt1 = i;
				locationForPt2 = j;
			}//if
				
		}//for
	}//for
	
}//void



int main () {
	int fileNumber;
	string fileOneName, fileTwoName;
	cout << "And type 1 if the input file is a file of numbers" << endl;
	cout << "Type 2 if the input file is a text file" << endl;


	cin >> fileNumber;
	if ( fileNumber == 1 ) { //numbers file;
		cout << "Type in the name of the input file: " << endl;
		cin >> fileOneName;
		ifstream myFile (fileOneName);
		int total2DPointsInFile;
		point2D **arrayToStore2DPoint;
		if ( myFile.is_open() ) {
			myFile >> total2DPointsInFile;
			arrayToStore2DPoint = new point2D* [total2DPointsInFile];
			int firstNum, secondNum;
			for ( int i = 0; i < total2DPointsInFile; i++ ) {
				myFile >> firstNum >> secondNum;
				arrayToStore2DPoint[i] = new point2D ( firstNum, secondNum ); //allocating 2 values in array[0], array[1], array[2]...etc;
			}
			//print out entire array;
			for ( int i = 0; i < total2DPointsInFile; i++ ) {
				cout << arrayToStore2DPoint[i] -> toString() << endl;  //each line should be written using the toString function of each object;
			}
			int location1ForFunction, location2ForFunction;
			ClosestPairBF ( arrayToStore2DPoint, total2DPointsInFile, location1ForFunction, location2ForFunction );
			cout << "location1: " << location1ForFunction << endl;
			cout << "location2: " << location2ForFunction << endl;
		}//if file is open;
		else {
			cout << "Sorry. Cannot locate your number file." << endl;
		}


	} //if; numbers file;
	 else { //a file of text;
	 	cout << "Type in the name of the input file: " << endl;
		cin >> fileTwoName;
		ifstream myFile (fileTwoName);
		int totalLineInFile;
		string stringInFile;


		// IMPORTANT: 
		// Notes in class:
		// for example, this is how your file looks like;
		// 	4\n
		// 	This \n
		// 	Is \n
		// 	a \n
		// 	test\n

		// So that getline(infile, line); treat the 4\n line's '\n' as another line;










		string emptyString = ""; 







		// *************** Begin Tutorial: *****************
		// getline function:
		// getline(infile, s);
		// s: by default, getline read s until it's '\n';

		// *************** END Tutorial: *****************




		if ( myFile.is_open() ) {	
			myFile >> totalLineInFile;
			// myFile >> emptyString;
			getline(myFile,emptyString); // read the rest of the empty first line;
			for ( int i = 0; i < totalLineInFile; i++ ) {
					getline ( myFile, stringInFile );
					// cout << stringInFile;
					if ( stringInFile[stringInFile.length()-1] == ' ' ) { //if stringInFile has has a space by the end of the line; I am not adding a space in my string'stringInFile'
						emptyString = emptyString + stringInFile;
						// cout << "testing in my if statement: " << endl;
						// cout << emptyString;
					}





	// string testString = "Hello World! ";
	// cout << testString [testString.length()-1] << endl; 
	// cout << testString[0] << endl;
	// cout << "length of String: " << testString.length() << endl;
	// cout << "length of String: " << testString[testString.length()] << endl;
	// if ( testString [testString.length()-1] == ' ' ) {
	// 	cout << "if statement works;" << endl;
	// } 
	// else {
	// 	cout << "if statement doesn't work" << endl;
	// }












					else {
						// cout << "testing in my else statement: " << endl;
						emptyString = emptyString + stringInFile + " ";
					}
					// if ()
					// 
					// emptyString = emptyString + stringInFile;
			}
			// getline ( myFile, token ); //save the line in token; getline returns a bool;
			// emptyString = token;


			// myFile >> totalLineInFile;
			// myFile >> token;
			// while ( myFile.get(token) ) {
			// 	getline (myFile, token);
			// 	cout << token;
			// }
			cout << "**************************** TESTING TO SEE EMPTYSTRING ****************************" << endl;
			cout << emptyString << endl;
			cout << "**************************** END TESTING TO SEE EMPTYSTRING ****************************" << endl;
// 			Your program should then ask the user for s string to
// search in the text from file. Be careful! the user input should be allowed to contain
// spaces, so you have to do the user input carefully.
			string userSearch;
			cout << "Now, let's search for a string in this text file. Please type in your search string." << endl;
			cout << "Search function will return the index of the first location in the first string input;" << endl;
			cout << "And -1 if the search cannot found." << endl;






			getline(cin, userSearch); // READS FROM THE PREVIOUS 'text1.txt\n'
			getline(cin, userSearch); //READS everything that user puts;
			//cin >> userSearch;
			// getline ()
			int indexOfUserSearch = StringMatchingBF ( emptyString, userSearch );


// ************************ BEGINING NOTES FROM CLASS; ************************


// NEED TO EDIT THIS PART:
// cin >> filename;
// cin >> type;
// getline ( cin, searchstr ); //just to pickup previous newline;
// cin >> searchstr;



// ************************  NOTES FROM CLASS; ************************










			cout << "The location for your string is: " << indexOfUserSearch << endl; 

		}//if file is open;

		else {
			cout << "Sorry. Cannot locate your text file." << endl;
		}//else
	}

	
}//main();



    // string STRING;
    // ifstream infile;
    // infile.open ("test.txt");
    // int a=0;
    // string previousLine="";
    // while(a<1) // To get you all the lines.
    // {
    //     getline(infile,STRING); // Saves the line in STRING.
    //     if (STRING != previousLine)
    //     {
    //         previousLine=STRING;
    //         cout<<STRING<<endl; // Prints our STRING.
    //     }

    // }
    // infile.close();
    // system ("pause");

// string str;
// string str1;
// string str2;
 
// cout<<"Enter a line of text: ";
// getline(cin, str);
// cout<<"You entered: "<<str<<endl;
// cout<<"Enter a line of text, <space> as the delimiter: "<<endl;
// getline(cin, str1, ' ');
// cout<<"You entered: "<<str1<<endl;



















// QUESTION: STORE STRING IN LINE;


    // char buffer[1024]; // line length is limited to 1023 bytes

    // std::ifstream file( "this.hash" );

    // while( file.good( ) ) {
    //     file.getline( buffer, sizeof( buffer ) );
    //     std::string line( buffer ); // convert to c++ string for convenience
    //     // do something with the line
    // }

    // return 0;
// }







