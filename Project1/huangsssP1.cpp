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

    ifstream file("tenNumbers.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
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
        

        pthread_t thread1, thread2, thread3, thread4; //4 threads;
        int half1, half2, half3, half4; //identify thread number;

        struct referenceArray * ptr1; //Making two pointers pointing to my struct;
        struct referenceArray * ptr2;
        struct referenceArray * ptr3;
        struct referenceArray * ptr4;


        ptr1 = new referenceArray; // Pointer pointing to my struct location;
        ptr2 = new referenceArray; 
        ptr3 = new referenceArray;
        ptr4 = new referenceArray;

        ptr1 -> totalNumber = n; // store n into totalNumber;
        ptr2 -> totalNumber = n;
        ptr3 -> totalNumber = n;
        ptr4 -> totalNumber = n;

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

        ptr3 -> half = 3;
        pthread_create ( &thread3, NULL, bubble_sort, (void *) ptr3 );

        ptr4 -> half = 4;
        pthread_create ( &thread4, NULL, bubble_sort, (void *) ptr4 );

        // must wait for children to finish before making the further step; which is to merge two sublists;
        pthread_join (thread1, NULL);
        pthread_join (thread2, NULL);
        pthread_join (thread3, NULL);
        pthread_join (thread4, NULL);

                

// Write down the sorted number in the already sorted array from two threads from the bubble_sort function to finalAnswer.txt

        if ( n % 2 == 0 ) { //even number of integers (N) from the .txt file.
            int i = 0; //location counter for the first part of the array;
            int j = 0; //location counter for the second part of the array;
            ofstream myFile;
            myFile.open ("finalAnswer.txt");
            if ( myArray[i] < myArray[n/2+j] ) { // if the first number from the first part of the array is less than the first number from the second part of the array;
                myFile << myArray[i] << endl;
                i++; //move my counter for the array location;
            }
            else {
                myFile << myArray[n/2+j] << endl; //else, move my counter from the second part of the array;
                j++;
            }
            //while the counter have not reaching to the end of both part of the array;
            while ( ( i < n/2 ) && ( j < n/2 ) ) {
                if ( myArray[i] < myArray[n/2+j] ) {
                    myFile << myArray[i] << endl;
                    i++;
                }
                else {
                    myFile << myArray[n/2+j] << endl;
                    j++;
                }

            }//while;

            // finish writing down the number from the array if there are any number left
            if ( i > j) {//if already finished printing first part of the array; then I need to finish printing from the second part of the array;
                for ( int k = j; k < n/2; k++ ) {//k is the already printed part of the second part of the array;
                    myFile << myArray[i+k] << endl;
                }
            }
            else {//if already finished printing second part of the array; then I need to finish printing from the first part of the array;
                for ( int k = i; k < n/2; k++ ) {
                    myFile << myArray[k] << endl;
                }
            }
            myFile.close();

        }//if. even number of integers (N) from the .txt file;
        else {//odd number of integers (N) from the file;
            int i = 0;
            int j = 0;

            ofstream myFile;
            myFile.open ("finalAnswer.txt");

            if ( myArray[i] < myArray[n/2+1+j] ) { // if the first number from the first part of the array is less than the first number from the second part of the array;
                myFile << myArray[i] << endl;
                i++; //move my counter for the array location;
            }
            else {
                myFile << myArray[n/2+1+j] << endl; //else, move my counter from the second part of the array;
                j++;
            }
            while ( ( i < n/2+1 ) && ( j < n/2 ) ) {
                if ( myArray[i] < myArray[n/2+1+j] ) {
                    myFile << myArray[i] << endl;
                    i++;
                }
                else {
                    myFile << myArray[n/2+1+j] << endl;
                    j++;
                }

            }//while;

            if ( i > j) {//if already finished printing first part of the array;
                for ( int k = j; k < n/2; k++ ) {
                    myFile << myArray[i+k] << endl;
                }
            }
            else {//if already finished printing second part of the array;
                for ( int k = i; k < n/2+1; k++ ) {
                    myFile << myArray[k] << endl;
                }
            }
            myFile.close();



        }



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

    
          
        

    }
    else if ( half == 2 ) {//thread2;

    }

    else if ( half == 3 ) {//thread3;

    }
























     else { //thread4;
       
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





