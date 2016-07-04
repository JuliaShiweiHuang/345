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

#include <stdio.h>   /* printf, fopen */
#include <stdlib.h> /* exit(-1) */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <iomanip>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;

char array[200][60]; //make array global so three threads could access the same array;
ifstream file ("input.txt");
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
	pthread_mutex_lock (&S_One);
	long someNum = (long) ptr;

	if ( someNum == 1 ) { //thread 1: put file into the 2d array;
		
		long col = 0;
		long row = 0;
		
		if ( file.is_open() ) { //if I could locate my file;

			while ( file.get(character) ) { //inserting characters into 2d array;

				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {
					row ++;
					col = 0;
				}//if
			}//while 
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
	
		for ( int i = 0; i < 200; i++ ) {
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

							char tmpArray[0][60];//make a tmp array to store the character right after /u
							int insideOneRow = j+2;
							bool noSpaceOrPunc = true;
							int countCharacter = 0;

							while ( noSpaceOrPunc ) { //stop right after space is found;
								if ( array[i][insideOneRow] == ' ' || array[i][insideOneRow] == ',' || array[i][insideOneRow] == '!' || array[i][insideOneRow] == '.' || array[i][insideOneRow] == '\n' ) {
									noSpaceOrPunc = false;
									array[i][j] = '_'; //substitute '/' into '_'
									array[i][j+countCharacter+1] = '_'; //substitute the last character before space into '_'
								}//if

								else {
									if ( insideOneRow < 60 ) {
										tmpArray[0][countCharacter] = array[i][insideOneRow];//putting the first character after '\u' into temp array;
										array[i][insideOneRow-1] = tmpArray[0][countCharacter];//relocate my first character into the original 'u' location;
										insideOneRow ++; //do this for the next character;
										countCharacter ++;
									}
								}//else

								

							}//while

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
	  	myfile.open ("output.txt");

		for ( int i = 0; i < 200; i++ ) {
		  	for ( int j = 0; j < 60; j++ ) {
		  		if ( array[i][j] != ' ' ) { //if array[i][j] is not space, put into the file;
		  			myfile << array[i][j];
		  		}//if
		  		else { //only adding manmaid space if word and space are saparated by 1 space ( rather than 2 spaces or 3 spaces );
		  			if ( ( array[i][j] == ' ' ) && ( array[i][j+1] != ' ' ) ) {
		  				myfile << " ";
		  			}//if
		  		}//else
		  	}//for
		}//for

		
	  	myfile.close();
	}

}//void















