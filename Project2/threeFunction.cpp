#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;
//Trying semaphore instead of mutex;
sem_t sem;
// sem_init(&sem, 0, 1);
long row;
long countRow = 0; // global count row for 2nd thread and 3rd thread;
char array[200][60];
ifstream file ("macInput.txt");
char character;

void * organizeGroup1 ( void * );
void * organizeGroup2 ( void * );
void * organizeGroup3 ( void * );

int main () {
	

	//initialize array;
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

	// pthread_mutex_lock (&S_One);
	pthread_mutex_lock(&S_Two);
	pthread_mutex_lock(&S_Three);

	group1 = 1;
	pthread_create (&thread1, NULL, organizeGroup1, (void *) group1);

	group2 = 2;
	pthread_create (&thread2, NULL, organizeGroup2, (void *) group2);

	group3 = 3;
	pthread_create (&thread3, NULL, organizeGroup3, (void *) group3);

// cin.get();

	pthread_join(thread1, NULL); //wait for thread1 to finish;
	pthread_join(thread2, NULL); //wait for thread2 to finish;
	pthread_join(thread3, NULL); //wait for thread3 to finish;

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);

	cout << "debug: main(){} done." << endl;

	return 0;

}

/*

If the mutex isn't currently locked by any thread, the calling thread locks it 
	(from this point, and until its member unlock is called, the thread owns the mutex).

If the mutex is currently locked by another thread, 
	execution of the calling thread is blocked until unlocked by the other thread (other non-locked threads continue their execution).

If the mutex is currently locked by the same thread calling this function, 
	it produces a deadlock (with undefined behavior). See recursive_mutex for a mutex type that allows multiple locks from the same thread.


*/
// Notes:

// because thread1 is never locked. when i went to the pthread_mutex_lock statement
// if it is unlocked,

// so i go through another loop
// until it is locked

// Then i go to the next statement


void * organizeGroup1 ( void* ptr) {
	pthread_mutex_lock (&S_One);
	long someNum = (long) ptr;
	// cout << "Debug: In threads, someNum = " << someNum << endl;

	if ( someNum == 1 ) {
		cout << "Debug: someNum == 1" << endl;
		long col = 0;
		row = 0;
		// long row = 0;
		
		if ( file.is_open() ) { //if I could locate my file;
			cout << "Debug. Yes. File is found. " << endl;
			while ( file.get(character) ) {

				array[row][col] = character;
				col ++;
				cout << character;

				if ( character == '\n' ) {
					cout << " - row: " << row <<endl;
					// pthread_mutex_lock (&S_Two);
					
					row ++;
					col = 0;
				}//if \n
			}//while get
			cout << " - row: " << row <<endl;
			countRow = row; //global variable count
			cout << "row before unlock2: " << countRow << endl;
			pthread_mutex_unlock (&S_Two);
			cout << "row after unlock2: " << countRow << endl;
		}//if file
		else {
			cout << "Sorry. Cannot locate your file." << endl;
		}
		
	}//if
}//void



void * organizeGroup2 ( void* ptr) {
	//cout << "start of organizeGroup2" << endl;
	pthread_mutex_lock (&S_Two);
	cout << "past lock in group 2" << endl;
	long someNum = (long) ptr;
	cout << "Debug: In thread 2, someNum = " << someNum << endl;
	cout << "Debug: In thread 2, row = " << row << endl;

	for ( int i = 0; i < row; i++ ) {
		for ( int j = 0; j < 60; j++ ) {
			if ( array[i][j] == '\\' ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j] = ' ';
						array[i][j+1] = ' ';
						array[i][j+2] = toupper( array[i][j+2] );
					}//if

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
		// cin.get();
		// pthread_mutex_unlock(&S_One);

	}//for
	pthread_mutex_unlock(&S_Three);

}//void


void * organizeGroup3 ( void* ptr) {
	pthread_mutex_lock (&S_Three);
	long someNum = (long) ptr;
	cout << "Debug: In threads, someNum = " << someNum << endl;
	ofstream myfile;
  	myfile.open ("macOutput.txt");

	for ( int i = 0; i < 200; i++ ) {
	  	for ( int j = 0; j < 60; j++ ) {
	  		if ( array[i][j] != ' ' ) { 
	  			myfile << array[i][j];
	  		}//if
	  		else { //only adding manmaid space if word and space are saparated by 1 space ( rather than 2 spaces or 3 spaces outputFileShiwei2);
	  			if ( ( array[i][j] == ' ' ) && ( array[i][j+1] != ' ' ) ) {
	  				myfile << " ";
	  			}//if
	  		}//else
	  	}//for
	}//for

	// cout << "5" << endl;
  	myfile.close();

  	// return 0;

}















