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

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <iomanip>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;

long row;
char array[200][60]; //make array global so three threads could access the same array;
ifstream file ("bob2.txt");
char character;

void * organizeGroup1 ( void * );
void * organizeGroup2 ( void * );
void * organizeGroup3 ( void * );

int main () {
	//initialize array into all spaces;
	for ( long i = 0; i < 200; i ++ ) {
		for ( long col = 0; col < 60; col ++ ) {
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
	pthread_create (&thread1, NULL, organizeGroup1, (void *) group1);

	group2 = 2;
	pthread_create (&thread2, NULL, organizeGroup2, (void *) group2);

	group3 = 3;
	pthread_create (&thread3, NULL, organizeGroup3, (void *) group3);

	pthread_join(thread1, NULL); //wait for thread1 to finish;
	pthread_join(thread2, NULL); //wait for thread2 to finish;
	pthread_join(thread3, NULL); //wait for thread3 to finish;

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);


	return 0;

}


void * organizeGroup1 ( void* ptr) { 
	cout << "cout statement to see whether what thread is printing" << endl;
	pthread_mutex_lock (&S_One);
	long someNum = (long) ptr;

	if ( someNum == 1 ) { //thread 1: put file into the 2d array;
		
		long col = 0;
		row = 0;
		
		if ( file.is_open() ) { //if I could locate my file;

			while ( file.get(character) ) { //inserting characters into 2d array;

				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {
					row ++;
					col = 0;
					
				}//if
				cout << array[row][col];
			}//while 
			cout << "statement before mutex2 unlock";
			pthread_mutex_unlock (&S_Two); //unlock 2nd thread;
			
		}//if file
		else {
			cout << "Sorry. Cannot locate your file." << endl;
			exit(-1);
		}//else
		
	}//if
}//void



void * organizeGroup2 ( void* ptr) {
	
	pthread_mutex_lock (&S_Two);
	long someNum = (long) ptr;

	if ( someNum == 2 ) { //thread2: take out control sequences from the 2d array;
	
		for ( int i = 0; i < row + 1; i++ ) {
			for ( int j = 0; j < 60; j++ ) {
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
									if ( insideOneRow < 60  ) {
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
							inword--;
							array[i][inword] = '_';//substitute the manmade space with '_'

						}//else

				}//if
				
			}//for
			

		}//for
	
		pthread_mutex_unlock(&S_Three);
	}//if
	

}//void


void * organizeGroup3 ( void* ptr) { //3rd thread process the array into a .txt file

	pthread_mutex_lock (&S_Three);
	long someNum = (long) ptr;
	
	if ( someNum == 3 ) {
		ofstream myfile;
	  	myfile.open ("boboutput1.txt");

	  	for ( int i = 0; i < row + 1; i ++ ) {
	  		int insideOneRowCounter = 0;
	  		while ( insideOneRowCounter < 60 && array[i][insideOneRowCounter] != '\n' ) {
	  			
	  			myfile << array[i][insideOneRowCounter];
	  			insideOneRowCounter ++;
	  		}

	  		myfile << '\n';
	  		
	  	}

	  	myfile.close();
	}

}//void














