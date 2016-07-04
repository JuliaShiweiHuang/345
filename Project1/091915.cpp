// Last edit: 20:39 09/19/2015; this is the WORKING VERSION of an integer array with MAX number of 10,000 integers;
// Reading from number.txt to array of integers;
// Sorted number is in "finalAnswer.txt"
// File reading algorithm is from the following: 
// http://www.cplusplus.com/forum/beginner/78150/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    ifstream file("number.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
    if( file.is_open() ) {
        int MAXINT;  // MAXINT variable: Max number of integers from the number.txt file; which is also the first line from the file; 
        int nextInt;
        file >> nextInt; //reads the first number from the file;
        MAXINT = nextInt; //since the file listed the total number of random number in the txt file. Thus, put nextInt into MAXINT variable.
        int myArray[MAXINT-1]; // making an integer array with Max number of integers;
//        putting the number of integers from .txt file to myArray
        for( int i = 0; i < MAXINT; ++i ) {
            file >> nextInt; //using for loop to put the number from the .txt file to myArray; Also note that nextInt is starting from the second number;
            myArray[i] = nextInt;
        }       
        
//        Begining part of BUBBLE SORT. Copied directly from 116 textbook. Chapter 19: Searching and Sorting Algorithm;
        for ( int iteration = 1; iteration < MAXINT; iteration++ ) {
            for ( int index = 0; index < MAXINT - iteration; index++ ) {
                if ( myArray[index] > myArray[index+1] ) {
                    int temp = myArray[index];
                    myArray[index] = myArray[index+1];
                    myArray[index+1] = temp;
                }//if
            }//for
        }//for
        
// write down the sorted number to finalAnswer.txt
    ofstream myFile;
    myFile.open ("finalAnswer.txt");

    for ( int i = 0; i < MAXINT; ++i ) {
            myFile << myArray[i] << endl;
    }
    myFile.close();
    return 0;
    }//if
    else { //if file not found. Show error message. 
        cout << "The file name you typed in does not exist. Please check whether you are in the correct directory." << endl;
    }
  
} //main();
