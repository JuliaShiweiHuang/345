#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct referenceArray {
    int half;
	// int start; //starting number for an array in one of the threads;
	// int end; //end number for the array in one of the threads;
    int totalNumber;
    int *arrayPointer;

};


void * bubble_sort ( void * );

int main() {

    ifstream file("tenNumbers.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
    if( file.is_open() ) {

        
        pthread_t thread1, thread2;
        int half1, half2;

        struct referenceArray * ptr1;
        struct referenceArray * ptr2;


        ptr1 = new referenceArray;
        ptr2 = new referenceArray; 

        int n;  //variable 'n': n = total number of integers from the number.txt file; which is also the first line from the file; 
        int nextInt;

        file >> nextInt; //reads the first number from the file;
        n = nextInt;



        ptr1 -> arrayPointer = new int[n];

       

        // cout << "This is just making sure that: this n should be 10 if done correctly !!! " << n << endl;

        // int *myArray = new int[n-1]; 

        for( int i = 0; i < n; ++i ) {
            file >> nextInt; //using for loop to put the number from the .txt file to myArray; Also note that nextInt is starting from the second number;
            arrayPointer[i] = nextInt;   
        }         
        // cout << "print statement myArray" << myArray[5] << endl;

        // ptr1 -> arrayPointer = &myArray[n-1];
        // ptr2 -> arrayPointer = &myArray[n-1];
        ptr1 -> totalNumber = n;
        // cout << "so that this pointer should print out n which is 10 if done correctly!!" << ptr1 -> totalNumber << endl;
        

// // MIGHT CAUSING ERROR
//         ptr1 -> numValue = n;
//         ptr2 -> numValue = n;

        ptr1 -> half = 1;
        pthread_create ( &thread1, NULL, bubble_sort, (void *) ptr1);

        ptr2 -> half = 2;
        pthread_create ( &thread2, NULL, bubble_sort, (void *) ptr2 );

        pthread_join (thread1, NULL);

        pthread_join (thread2, NULL);

    }//if
    else {
    	cout << "Error: File cannot found" << endl;
    }//else

    return 0;
}


void * bubble_sort (void * ptr) {

    struct referenceArray * local_ptr = ( struct referenceArray *) ptr;
    int half = local_ptr -> half;
    // int start = local_ptr -> start;
    // int end = local_ptr -> end;
    int *arrayPointer = local_ptr -> arrayPointer;
    int totalNumber = local_ptr -> totalNumber;
    if ( half == 1 ) { //thread1;
        cout << arrayPointer[2]  << endl;
        // cout << &myArray[2] << endl;
        // for ( int iteration = 1; iteration < totalNumber/2; iteration++ ) {
        //     for ( int index = 0; index < totalNumber/2 - iteration; index++ ) {
        //         cout << myArray[2] << "SHOULD BE eleven!!" << endl;
        //     }

        //}






    } 
    //else { //thread2;
    //     cout << "this is bubble_sort function thread2" << endl;
    // }


// //        Begining part of BUBBLE SORT. Copied directly from 116 textbook. Chapter 19: Searching and Sorting Algorithm;
//         for ( int iteration = 1; iteration < MAXINT; iteration++ ) {
//             for ( int index = 0; index < MAXINT - iteration; index++ ) {
//                 if ( myArray[index] > myArray[index+1] ) {
//                     int temp = myArray[index];
//                     myArray[index] = myArray[index+1];
//                     myArray[index+1] = temp;
//                 }//if
//             }//for
//         }//for
        







// Write File in .txt files


}




















