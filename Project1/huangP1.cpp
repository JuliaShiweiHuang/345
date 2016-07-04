/*
 * Shiwei Huang
 * CS345: huangP1.cpp
 * Purpose: Usings threads to sort a list of number from .txt file. 
 *          Output two sorted number lists from two threads. Merge the main sorted list in the main and output the main file.
 * Input: a .txtfile contains data, which is a list of integers to be sorted. The first line of the file will contain N, which is number of values in the file. 
   This is followed by N lines, where each line contains one integer value.
 * Output: The program will create three text files. The first two file is sorted sublists created by each thread.
   The last file is the final sorted list, called finalAnswer.txt
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct referenceArray { 
    int half; // which half of the thread is computing;
    int totalNumber; // total number of integers from the main .txt file;
    int *arrayPointer; // from the referenceArray struct, making a pointer pointing the array constructed from the main function;

};


void * bubble_sort ( void * ); // in the thread, using bubble sort function to sort two sublists;

int main() {

    ifstream file("number.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
    if( file.is_open() ) {

        int n;  //variable 'n': n = total number of integers from the number.txt file; which is also the first line from the file; 
        int nextInt;
        file >> nextInt; //reads the first number from the file;
        n = nextInt; // store the first line from the file (N integers) into variable n;

        int *myArray = new int[n]; //making a dynamic array containing n integers;

        for( int i = 0; i < n; ++i ) { //using for loop to put the number from the .txt file to myArray; 
            file >> nextInt; //Also note that nextInt is starting from the second number;
            myArray[i] = nextInt;   
        }         
        

        pthread_t thread1, thread2; //2 threads;
        int half1, half2; //identify thread number;

        struct referenceArray * ptr1; //Making two pointers pointing to my struct;
        struct referenceArray * ptr2;


        ptr1 = new referenceArray; // Pointer pointing to my struct location;
        ptr2 = new referenceArray; 

        ptr1 -> totalNumber = n; // store n into totalNumber;
        ptr2 -> totalNumber = n;

        if ( n % 2 == 0 ) { // total number N from the file is even;
            ptr1 -> arrayPointer = &myArray[0];
            ptr2 -> arrayPointer = &myArray[n/2];
        }

        else { // total number N from the file is odd;
            ptr1 -> arrayPointer = &myArray[0];
            ptr2 -> arrayPointer = &myArray[n/2+1];

        }

        
        ptr1 -> half = 1;
        pthread_create ( &thread1, NULL, bubble_sort, (void *) ptr1);
      
        ptr2 -> half = 2;
        pthread_create ( &thread2, NULL, bubble_sort, (void *) ptr2 );

        // must wait for children to finish before making the further step; which is to merge two sublists;
        pthread_join (thread1, NULL);
        pthread_join (thread2, NULL);

                
// Bubble sort. Copied directly from 116 textbook. Chapter 19: Searching and Sorting Algorithm;
        for ( int iteration = 1; iteration < n; iteration++ ) {
            for ( int index = 0; index < n - iteration; index++ ) {
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

        for ( int i = 0; i < n; ++i ) {
                myFile << myArray[i] << endl;
        }
        myFile.close();


    }//if
    else {
    	cout << "Error: File cannot found" << endl;
    }//else

    return 0;
} //main;


void * bubble_sort (void * ptr) { //passing the pointer and make it pass by reference;

    struct referenceArray * local_ptr = ( struct referenceArray *) ptr; // making void pointer and recast it back to struct referenceArray;
    int half = local_ptr -> half;
    int *arrayPointer = local_ptr -> arrayPointer;
    int totalNumber = local_ptr -> totalNumber;
   
    if ( half == 1 ) { //thread1;
        if ( totalNumber % 2 == 0 ) {//totalNumber N from the file is even;
            for ( int iteration = 1; iteration < totalNumber/2; iteration++ ) {
                for ( int index = 0; index < totalNumber/2 - iteration; index++ ) {
                    if ( local_ptr -> arrayPointer[index] > arrayPointer[index+1] ) {
                        int temp = local_ptr -> arrayPointer[index];
                        local_ptr -> arrayPointer[index] = arrayPointer[index+1];
                        local_ptr -> arrayPointer[index+1] = temp;
                    }//if
                }//for
            }//for
        
     
            ofstream myFile;
            myFile.open ("sorted1.txt");
            for ( int i = 0; i < totalNumber/2; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();

    
        } else { //totalNumber N from the file is odd;
            for ( int iteration = 1; iteration < totalNumber/2+1; iteration++ ) {
                for ( int index = 0; index < totalNumber/2+1 - iteration; index++ ) {
                    if ( local_ptr -> arrayPointer[index] > arrayPointer[index+1] ) {
                        int temp = local_ptr -> arrayPointer[index];
                        local_ptr -> arrayPointer[index] = arrayPointer[index+1];
                        local_ptr -> arrayPointer[index+1] = temp;
                    }//if
                }//for
            }//for
        
     
            ofstream myFile;
            myFile.open ("sorted1.txt");
            for ( int i = 0; i < totalNumber/2+1; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();
        }//else. totalNumber in file is odd;

    } //thread1

     else { //thread2;
       
            for ( int iteration = 1; iteration < totalNumber/2; iteration++ ) {
                for ( int index = 0; index < totalNumber/2 - iteration; index++ ) {
                    if ( local_ptr -> arrayPointer[index] > arrayPointer[index+1] ) {
                        int temp = local_ptr -> arrayPointer[index];
                        local_ptr -> arrayPointer[index] = arrayPointer[index+1];
                        local_ptr -> arrayPointer[index+1] = temp;
                    }//if
                }//for
            }//for

         
            ofstream myFile;
            myFile.open ("sorted2.txt");
            for ( int i = 0; i < totalNumber/2; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();

   
       
    }//else; finish thread2;


}//void





