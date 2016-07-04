#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct referenceArray {
    int half;
    int totalNumber;
    int *arrayPointer;

};


void * bubble_sort ( void * );

int main() {

    ifstream file("fiveNumbers.txt"); //number.txt downloaded directly from http://cs.wheatonma.edu/mgousie/comp345/randomNums.txt
    if( file.is_open() ) {

        int n;  //variable 'n': n = total number of integers from the number.txt file; which is also the first line from the file; 
        int nextInt;
        file >> nextInt; //reads the first number from the file;
        n = nextInt;

        // cout << "This is just making sure that: this n should be 10 if done correctly !!! " << n << endl;
        int *myArray = new int[n]; 

        for( int i = 0; i < n; ++i ) {
            file >> nextInt; //using for loop to put the number from the .txt file to myArray; Also note that nextInt is starting from the second number;
            myArray[i] = nextInt;   
        }         
        
        //   cout << "this is in my main" << endl;
        // cout << "1th: " << myarray[1] << endl;
        // cout << "2th: " << myarray[2] << endl;
        // cout << "3th: " << local_ptr -> arrayPointer[3] << endl;
        // cout << "4th: " << local_ptr -> arrayPointer[4] << endl;
        // cout << "5th: " << local_ptr -> arrayPointer[5] << endl;
        // cout << "6th: " << local_ptr -> arrayPointer[6] << endl;
        // cout << "7th: " << local_ptr -> arrayPointer[7] << endl;
        // cout << "8th: " << myarray[8] << endl;
        // cout << "9th: " << myarray[9] << endl;

        pthread_t thread1, thread2;
        int half1, half2;

        struct referenceArray * ptr1;
        struct referenceArray * ptr2;


        ptr1 = new referenceArray;
        ptr2 = new referenceArray; 

        ptr1 -> totalNumber = n;
        ptr2 -> totalNumber = n;

        ptr1 -> arrayPointer = &myArray[0];
        ptr2 -> arrayPointer = &myArray[n /2];


        ptr1 -> half = 1;
        pthread_create ( &thread1, NULL, bubble_sort, (void *) ptr1);
         int something1;
        cin >> something1;
        ptr2 -> half = 2;
        pthread_create ( &thread2, NULL, bubble_sort, (void *) ptr2 );

        int something;
        cin >> something;

        pthread_join (thread1, NULL);
       
        int somethingelse;
        cin >> somethingelse;

        pthread_join (thread2, NULL);

    }//if
    else {
    	cout << "Error: File cannot found" << endl;
    }//else

    return 0;
} //main;


void * bubble_sort (void * ptr) {

    struct referenceArray * local_ptr = ( struct referenceArray *) ptr;
    int half = local_ptr -> half;
    int *arrayPointer = local_ptr -> arrayPointer;
    int totalNumber = local_ptr -> totalNumber;
   
    if ( half == 1 ) { //thread1;
        if ( totalNumber % 2 == 0 ) { // if "totalNumber" is an even number;
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
            myFile.open ("testPart1.txt");
            for ( int i = 0; i < totalNumber/2; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();

        }//if 

        else { // if "totalNumber" is an odd number;
            for ( int iteration = 1; iteration < totalNumber/2+1; iteration++ ) {
                for ( int index = 0; index < totalNumber/2 + 1 - iteration; index++ ) {
                    if ( local_ptr -> arrayPointer[index] > arrayPointer[index+1] ) {
                        int temp = local_ptr -> arrayPointer[index];
                        local_ptr -> arrayPointer[index] = arrayPointer[index+1];
                        local_ptr -> arrayPointer[index+1] = temp;
                }//if
            }//for
        }//for

            ofstream myFile;
            myFile.open ("testPart1.txt");
            for ( int i = 0; i < totalNumber/2+1; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();
        }


    } 

     else { //thread2;
        // if ( totalNumber % 2 == 0 ) { // if "totalNumber" is an even number;

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
            myFile.open ("testPart2.txt");
            for ( int i = 0; i < totalNumber/2; ++i ) {
                myFile << local_ptr -> arrayPointer[i] << endl;
            }
            myFile.close();

        // } //end if "totalNumber" is an even number;

        // else { // if "totalNumber" is an odd number;
        //     for ( int iteration = 1; iteration < totalNumber/2+1; iteration++ ) {
        //         for ( int index = 0; index < totalNumber/2 + 1 - iteration; index++ ) {
        //             if ( local_ptr -> arrayPointer[index] > arrayPointer[index+1] ) {
        //                 int temp = local_ptr -> arrayPointer[index];
        //                 local_ptr -> arrayPointer[index] = arrayPointer[index+1];
        //                 local_ptr -> arrayPointer[index+1] = temp;
        //         }//if
        //     }//for
        // }//for

        //     ofstream myFile;
        //     myFile.open ("testPart2.txt");
        //     for ( int i = 0; i < totalNumber/2+1; ++i ) {
        //         myFile << local_ptr -> arrayPointer[i] << endl;
        //     }
        //     myFile.close();
        // }
       
    }


}




















