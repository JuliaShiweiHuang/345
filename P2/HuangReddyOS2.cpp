/*
Comp345: Project OS2
Buddies: Shiwei Huang and Kristina Reddy 
Purpose: Use three threads to 
1. process a .txt file to a 2d 200(row)*60(col) array
2. take out control sequences including \c, \C and \u
3. make my formatted array into a new .txt file.

Input: 
1) Input from keyboard:
    a text file of any length
    the file will contain normal words and punctuation, and may contain control sequences.

2) Input from the console:
	The program should prompt for the name of the file

Output:
1) A new file
   The .txt file has taken out control sequences, delete the control sequences themselves. 
   The resulting text should be both left and right justified.
2) The result of the text processing on the console.
*/


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

pthread_mutex_t S_One, S_Two, S_Three; //three mutexs;
long row; //counter to see how many rows the .txt file has;
const long TOTAL_ROW = 200;
const long TOTAL_COL = 60;
char array[TOTAL_ROW][TOTAL_COL]; //make array global so three threads could access the same array;
ifstream inputFile("input.txt");

//function declaration;
void * store_in_file ( void * );
void * take_control_sequence ( void * );
void * display_out_file ( void * );

int main () {
	//initialize array into all spaces;
	for ( long i = 0; i < TOTAL_ROW; i ++ ) {
		for ( long col = 0; col < TOTAL_COL; col ++ ) {
			array[i][col] = ' ';
		}
	}

	//create 3 threads;
	pthread_t thread1, thread2, thread3;
	long group1, group2, group3;

	//mutax initialization;
	pthread_mutex_init(&S_One, NULL);
	pthread_mutex_init(&S_Two, NULL);
	pthread_mutex_init(&S_Three, NULL);

    // lock 2nd and 3rd thread so the 1st thread could go first;
	pthread_mutex_lock(&S_Two);
	pthread_mutex_lock(&S_Three);

	group1 = 1;
	pthread_create (&thread1, NULL, store_in_file, (void *) group1);

	group2 = 2;
	pthread_create (&thread2, NULL, take_control_sequence, (void *) group2);

	group3 = 3;
	pthread_create (&thread3, NULL, display_out_file, (void *) group3);

	pthread_join(thread1, NULL); //wait for thread1 to finish;
	pthread_join(thread2, NULL); //wait for thread2 to finish;
	pthread_join(thread3, NULL); //wait for thread3 to finish;

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);

	

	return 0;

}


/*
Function description: this function takes a .txt file and store into a 2d array; when the first thread is going and becaue the first
thread is in the unlock condition, row will be incremented twice (row = 1);

Pre-condition: First, group 1 = 1 is passed to store_in_file as a pointer. 2. file exists
Post-condition: The text from .txt file is stored into the 2d array.

return: none;
*/

void * store_in_file ( void* ptr) { 
	
	long someNum = (long) ptr;

	if ( someNum == 1 ) { //thread 1: put the content from file into the 2d array;
		
		long col = 0;
		row = 0;
		char character;

		if ( inputFile.is_open() ) { //if I could locate my file;
		
			while ( inputFile.get(character) ) { //inserting characters into 2d array;
				
				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {//increment row once reaches '\n'

					// cout << "thread1" << endl;
					// cout << "lock one " << endl;

					pthread_mutex_lock (&S_One); 

					// cout << "thread1 row: " << row << endl;
					// cout << "lock1" << endl;

					row ++;

					// cout << "thread1 row: " << row << endl;

					col = 0;

					// cout << "mutex2 unlocked " << endl;

					pthread_mutex_unlock (&S_Two); //unlock 2nd thread;

					// cout << "unlock2" << endl;
					
				}//if
			

			}//while 
			// cout << "thread1: finish after while loop" << endl;
			// cout << "thread1 row: " << row << endl;
			row --; //in order to let thread 3 finish for the purpose of last loop around;
			// cout << "thread1 row: " << row << endl;
			
			
			
		}//if file
		else {
			cout << "Sorry. Cannot locate your file." << endl;
			exit(-1);
		}//else
		
	}//if
}//void


/*
Function description: this function handles control sequence from the 2d array;

Pre-condition: in the main group2 = 2 is passing by as a pointer to this function;
Post-condition: the function takes out control sequence once thread1 puts the char in the array row. 

return: none;
*/


void * take_control_sequence ( void* ptr) {
	

	long someNum = (long) ptr;

	if ( someNum == 2 ) { //thread2: take out control sequences from the 2d array;
	
		for ( int i = 0; i < row+1; i++ ) {

			pthread_mutex_lock (&S_Two);
			// cout << "mutex2 locked " << endl;
			// cout << "thread2 i: " << i << endl;
			// cout << "thread2 row: " << row << endl;

			for ( int j = 0; j < TOTAL_COL; j++ ) {
				if ( array[i][j] == '\\' ) { // if '\' location is found;
						if ( array[i][j+1] == 'c' ) { //locate the next space right after '\'
							array[i][j] = ' '; //substitute '\\' location into space;
							array[i][j+1] = ' '; //substitute 'c' location into space;
							array[i][j+2] = toupper( array[i][j+2] ); //capitalize 2 places after '\' is found;
						}//if

						else if ( array[i][j+1] == 'C' ) {
							bool noSpace = true;
							int insideOneRow = j+2;
							while ( noSpace ) { //immediately stop if space is found (in order to identify the length of the word)
								if ( array[i][insideOneRow] == ' ' ) { 
									noSpace = false;
								}//if
								else {
									if ( insideOneRow < TOTAL_COL  ) {
										array[i][j] = ' '; //substitute '\\' location into space;
										array[i][j+1] = ' '; //substitute 'C' location into space;
										array[i][insideOneRow] = toupper( array[i][insideOneRow] ); //while loop and if statement will make array[i][insideOneRow] into upper case one at a time.
										insideOneRow ++; //increment the counter for the character that needs to be capitalized.
									}
								}//else
							}//while;
						}//else if

						else { // array[i][j+1] == 'u'

							int inword = j+1;
							array[i][j] = '_';

							while ( array[i][inword] != ' ' ) {
							
								if ( array[i][inword+1] == '\n' ) {// if at the [\uthe end of the word] reaches to the end of line character;
								
									array[i][inword+2] = array[i][inword+1];
									array[i][inword+1] = ' '; //made a manmade space at the original \n place;
								}
								//Two purposes for the next line:
								// 1. When the word not reaching at the end of line character, I shifted the character by -1 in the array;
								// 2. When the word reaches the end of line character, I copied the space from my previous if statement and add to the position RIGHT AFTER the word
								// for example: the original word is: \usome\n becomes _some(space). In order to jump out from the while loop.
								array[i][inword] = array[i][inword+1]; 
								inword++;
							}
							inword --;
							array[i][inword] = '_';//substitute the manmade space with '_'

						}//else

				}//if
				
			}//for
		// cout << "mutex3 unlocked " << endl;
		pthread_mutex_unlock(&S_Three);
		// cout << "unlock3" << endl;
		}//for

	}//if
	

}//void

/*
Function description: this function displays text from 2d array to the file;

Pre-condition: in the main group3 = 3 is passing by as a pointer to this function;
Post-condition: the function output the file. also output on the console.

return: none;
*/

void * display_out_file ( void* ptr) { //3rd thread process the array into a .txt file

	
	long someNum = (long) ptr;
	ofstream outputFile("output.txt");
	if (outputFile.is_open()){
	
		if ( someNum == 3 ) {
			
		  	
			// print array with correct space length;
		  	for ( int i = 0; i < row+1; i++ ) {
		  		// cout << "thread3 for loop" << endl;
		  		// cout << "thread3 row: " << row << endl;
		  		// cout << "thread3 i: " << i << endl;
		  		pthread_mutex_lock (&S_Three);
		  		// cout << "mutex3 locked " << endl;
		  		for ( int j = 0; j < TOTAL_COL; j++ ) {
		  			if ( array[i][j] != ' ' ) {
		  				cout << array[i][j];
		  				outputFile << array[i][j];
		  			}//if

		  			else {
		  				if ( ( array[i][j] == ' ' ) && ( array[i][j+1] != ' ' ) ) { // else, add a space only if there is a space RIGHT BEFORE the character;
		  					cout << " ";
		  					outputFile << " ";
		  				}
		  			}

		  		}
		  		
		  		// cout << "mutex1 unlocked " << endl;
		  		pthread_mutex_unlock (&S_One);
		  		// cout << "unlock1" << endl;
		  		// cout << "thread3" << endl;
		  		
		  		
		  	}

		  	outputFile.close();

		}

	}
	

}//void







