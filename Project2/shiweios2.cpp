#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;

struct referenceArray {
	int group;
	int *arrayPointer;
};

void * organizeArray ( void * );

int main () {

	ifstream file ("test.txt");
	char character;
	char array[200][60];

	//initialize array;
	for ( int row = 0; row < 200; row ++ ) {
		for ( int col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}


	pthread_t thread1, thread2, thread3;
	int group1, group2, group3;

	pthread_mutex_init(&S_One, NULL);
	pthread_mutex_init(&S_Two, NULL);
	pthread_mutex_init(&S_Three, NULL);

	pthread_mutex_lock(&S_Two);
	pthread_mutex_lock(&S_Three);

	struct referenceArray *ptr1;
	struct referenceArray *ptr2;
	struct referenceArray *ptr3;

	ptr1 = new referenceArray;
	ptr2 = new referenceArray;
	ptr3 = new referenceArray;

	ptr1 -> arrayPointer = &array[0][0];
	ptr2 -> arrayPointer = &array[0][0];
	ptr3 -> arrayPointer = &array[0][0];

	ptr1 -> group = 1;
	pthread_create(&thread1, NULL, referenceArray, (void *) ptr1);
	ptr2 -> group = 2;
	pthread_create(&thread2, NULL, referenceArray, (void *) ptr2);
	ptr3 -> group = 3;
	pthread_create(&thread3, NULL, referenceArray, (void *) ptr3);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);

	return 0;

}

void * organizeArray (void *ptr) {
	struct referenceArray * local_ptr = (struct referenceArray *) ptr;
	int *arrayPointer = local_ptr -> arrayPointer;

	int group1 = (int) ptr;
	int group2 = (int) ptr;
	int group3 = (int) ptr;

	if ( group1 ) {
		while ( file.get(character) ) {
			array[row][col] = character;
			col ++;
			if ( character == '\n' ) {
				pthread_mutex_unlock(&S_Two);
				pthread_mutex_lock(&S_One);
				row ++;
				col = 0;
			}//if
		}//while;
	}//if

	else if ( group2 ) {
		pthread_mutex_lock(&S_Two);
		for ( int j = 0; j < 60; j++ ) {
			if (array[row][j] == '\\') {
				if ( array[row][j+1] == 'c' ) {
						array[row][j] = ' ';
						array[row][j+1] = ' ';
						array[row][j+2] = toupper( array[i][j+2] );
				}//if c;
			}//if

			else if ( array[row][j+1] == 'C' ) {
				bool noSpace = true;
				int insideOneRow = j+2;
				while ( noSpace ) {
					if ( array[row][insideOneRow] == ' ' ) {
						noSpace = false;
					}
					else {
						if ( insideOneRow < 60  ) {
							array[row][j] = ' ';
							array[row][j+1] = ' ';
							array[row][insideOneRow] = toupper( array[i][insideOneRow] );
							insideOneRow ++;
						}//if
					}//else
				}//while;
			}//else if

			else { // array[i][j+1] == 'u'

				char tmpArray[0][60];
				int insideOneRow = j+2;
				bool noSpaceOrPunc = true;
				int countCharacter = 0;
						
				while ( noSpaceOrPunc ) {
					if ( array[row][insideOneRow] == ' ' || array[row][insideOneRow] == ',' || array[row][insideOneRow] == '!' || array[row][insideOneRow] == '.' || array[row][insideOneRow] == '\n' ) {
						noSpaceOrPunc = false;
						array[row][j] = '_';
						array[row][j+countCharacter+1] = '_';
					}//if

					else {
						if ( insideOneRow < 60 ) {
							tmpArray[0][countCharacter] = array[row][insideOneRow];
							array[row][insideOneRow-1] = tmpArray[0][countCharacter];
							insideOneRow ++;
							countCharacter ++;
						}//if
					}//else

				}//while
			}//else u;

		}//for
		// pthread_mutex_lock(&S_Two);
		pthread_mutex_unlock(&S_Three);
	}//else if
 
 	else {//group3;
 		pthread_mutex_lock(&S_Three);
 		ofstream myfile;
  		myfile.open ("hopeOutput.txt");

 		for (int j = 0; j < 60; j++ ) {
 			if ( array[i][j] != ' ' ) {
 				myfile << array[i][j];
 			}//if;

 			else {
 				if (( array[i][j] == ' ' ) && ( array[i][j+1] != ' ' )) {
 					myfile << " ";
 				}//if
 			}//else;
 		}//for;

 		// pthread_mutex_lock(&S_Three);
 		pthread_mutex_unlock(&S_One);

 	}//else

 	



}//void



















