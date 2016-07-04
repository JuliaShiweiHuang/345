#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>


using namespace std;

pthread_mutex_t S;	// semaphore

void * organizeArray (void *);


struct 2dArray {
	int *arrayPointer;

}


int main () {
	ifstream file ( "testSlash.txt" );
	char character;
	char array[200][60];
	int parallelArray[200][60];
	int row = 0, col = 0;

	// 2D Array initialization
	for ( int row = 0; row < 200; row ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}

	// make a parallel array in order to identify the '/' location
	// parallelArray initialization;
	for ( int i = 0; i < 200; i ++ ) {
		for ( int j = 0; j < 60; j++ ) {
			parallelArray[i][j] = 0;
		}
	}

	pthread_t thread1, thread2, thread3;
	int group1, group2, group3;

	pthread_mutex_init (&S, NULL);


   group1 = 1;
   pthread_create (&thread1, NULL, organizeArray, (void *) group1);
   group2 = 2;
   pthread_create (&thread2, NULL, organizeArray, (void *) group2);
   group1 = 3;
   pthread_create (&thread1, NULL, organizeArray, (void *) group3);

   pthread_join (thread1, NULL);  // wait for thread1 to finish
   pthread_join (thread2, NULL);  // wait for thread2 to finish
   pthread_join (thread3, NULL);  // wait for thread3 to finish



   pthread_mutex_destroy (&S);    // deallocate semaphore

   cout << " " << endl;

   return 0;
}



void * organizeArray ( void* ptr ) {
	
	int threadArrivedFirst = ( int ) ptr;

	if ( threadArrivedFirst == 1 ) { //first thread;
		if ( file.is_open() ) { //if I could locate my file;
			while ( file.get(character) ) {
				array[row][col] = character;
				col ++;
				if ( character == '\n' ) {
					pthread_mutex_lock (&S2 && &S3);	
					row ++;
					col = 0;
				}//if

				
			}//while
		} //if

	}


	else if { //second thread;

	
		// Making sure control sequence works;
	for ( int i = 0; i < 200; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( parallelArray[i][j] == 1 ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j] = ' ';
						array[i][j+1] = ' ';
						array[i][j+2] = toupper( array[i][j+2] );
					}


// FIX TAKING OUT OF CONTROL SEQUENCE ISSUE

					else if ( array[i][j+1] == 'C' ) {
						bool noSpace = true;
						int insideOneRow = j+2;
						while ( noSpace ) {
							if ( array[i][insideOneRow] == ' ' ) {
								noSpace = false;
							}
							else {
								if ( insideOneRow < 60  ) {
									array[i][j] = ' ';
									array[i][j+1] = ' ';
									array[i][insideOneRow] = toupper( array[i][insideOneRow] );
									insideOneRow ++;
								}
							}
						}//while;
					}//else if

					else { // array[i][j+1] == 'u'

						char tmpArray[0][60];
						int insideOneRow = j+2;
						bool noSpaceOrPunc = true;
						int countCharacter = 0;

						while ( noSpaceOrPunc ) {
							if ( array[i][insideOneRow] == ' ' || array[i][insideOneRow] == ',' || array[i][insideOneRow] == '!' || array[i][insideOneRow] == '.' || array[i][insideOneRow] == '\n' ) {
								noSpaceOrPunc = false;
								array[i][j] = '_';
								array[i][j+countCharacter+1] = '_';
							}//if

							else {
								if ( insideOneRow < 60 ) {
									tmpArray[0][countCharacter] = array[i][insideOneRow];
									array[i][insideOneRow-1] = tmpArray[0][countCharacter];
									insideOneRow ++;
									countCharacter ++;
								}
							}//else

						}//while

					}//else
			}//if
		}//for
	}//for






	}
	else { //third thread;

	}

	


}



