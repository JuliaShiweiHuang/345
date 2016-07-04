#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct referenceArray {
	int numValue; //number of values in an array;
	int half;
	// int myArray[NULL];
};

void * bubble_sort ( void * );

int main() {

    ifstream file("tenNumbers.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
    if( file.is_open() ) {
        int n;  //variable 'n': Max number of integers from the number.txt file; which is also the first line from the file; 
        int nextInt;
        file >> nextInt; //reads the first number from the file;
        n = nextInt; //since the file listed the total number of random number in the txt file. Thus, put nextInt into MAXINT variable.
        int myArray[n-1]; // making an integer array with Max number of integers;
//        putting the number of integers from .txt file to myArray
        for( int i = 0; i < n; ++i ) {
            file >> nextInt; //using for loop to put the number from the .txt file to myArray; Also note that nextInt is starting from the second number;
            myArray[i] = nextInt;   
        }         

        pthread_t thread1, thread2;
        int half1, half2;

        struct referenceArray * ptr1;
        struct referenceArray * ptr2;

        ptr1 = new referenceArray;
        ptr2 = new referenceArray; 

// MIGHT CAUSING ERROR
        ptr1 -> numValue = n;
        ptr2 -> numValue = n;

        ptr1 -> half = 1;
        pthread_create ( &thread1, NULL, bubble_sort, (void *) ptr1 );

        ptr2 -> half = 2;
        pthread_create ( &thread2, NULL, bubble_sort, (void *) ptr2 );


    }//if
    else {
    	cout << "Error: File cannot found" << endl;
    }//else

    return 0;
}

void * bubble_sort (void * ptr) {

	struct referenceArray * local_ptr = ( struct referenceArray *) ptr;

	int half = local_ptr -> half;
	int numValue = local_ptr -> numValue;


// QUESTIONS: HOW TO MAKE A LOCAL POINTER POINTING TO THE ARRAY IN MAIN()



	// int myArray[NULL] = local_ptr -> myArray[numValue];

	if ( half == 1 ) { //thread 1;
		  //        Begining part of BUBBLE SORT. Copied directly from 116 textbook. Chapter 19: Searching and Sorting Algorithm;
        for ( int iteration = 1; iteration < numValue/2+1; iteration++ ) {
            for ( int index = 0; index < numValue/2+1 - iteration; index++ ) {
                if ( myArray[index] > myArray[index+1] ) {
                    int temp = myArray[index];
                    myArray[index] = myArray[index+1];
                    myArray[index+1] = temp;
                }//if
            }//for
        }//for

        ofstream myFile;
        myFile.open ("sorted1.txt");
        for ( int i = 0; i < numValue/2+1; ++i ) {
            myFile << myArray[i] << endl;
        }
        myFile.close();
    } else { //thread 2;
		
	}




// Write File in .txt files


}
















