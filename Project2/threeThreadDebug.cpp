#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;

long row = 0;

void * organizeArray ( void * );


int main () {
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
	pthread_create (&thread1, NULL, organizeArray, (void *) group1);

	group2 = 2;
	pthread_create (&thread1, NULL, organizeArray, (void *) group2);

	group3 = 3;
	pthread_create (&thread1, NULL, organizeArray, (void *) group3);


	pthread_join(thread1, NULL); //wait for thread1 to finish;
	pthread_join(thread2, NULL); //wait for thread2 to finish;
	pthread_join(thread3, NULL); //wait for thread3 to finish;

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);

	cout << "debug: main(){} done." << endl;

	return 0;

}


void * organizeArray ( void* ptr) {

	ifstream file ("smalltest.txt");
	char character;
	char array[200][60];

	//initialize array;
	for ( long i = 0; i < 200; i ++ ) {
		for ( long col = 0; col < 60; col ++ ) {
			array[i][col] = ' ';
		}
	}

	long someNum = (long) ptr;
	cout << "Debug: In thread, someNum = " << someNum << endl;

	if ( someNum == 1 ) {
		
		long col = 0;
		
		if ( file.is_open() ) { //if I could locate my file;
			while ( file.get(character) ) {
				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {
					// pthread_mutex_lock (&S_One);
					pthread_mutex_unlock (&S_Two);
					row ++;
					col = 0;

				}//if
			}//while
			cout << "Debug: someNum == 1 where is first thread??" << endl;
				cout << "first thread:" << endl;
	  		cout << array[0][0];
	  		cout << array[0][1];
	  		cout << array[0][2];
	  		cout << array[0][3];
	  		cout << array[0][4];
		}//if
		

	}//if
	else if ( someNum == 2 ){
		pthread_mutex_lock (&S_Two);
		cout << "Debug: someNum == 2" << endl;
		for ( int i = row; i < 200; i++ ) {
			for ( int j = 0; j < 60; j++ ) {
				if ( array[i][j] == '\\ ' ) {
					if ( array[i][j+1] == 'c' ) {
						array[i][j] = ' ';
						array[i][j+1] = ' ';
						array[i][j+2] = toupper(array[i][j+2]);
					}

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
			pthread_mutex_unlock (&S_Three);

		}

		
	}
	else { //someNum == 3
		pthread_mutex_lock (&S_Three);
		cout << "Debug: someNum == 3" << endl;
		ofstream myfile;
  		myfile.open ("mutexOutput.txt");
  	
  		for ( int i = row; i < 200; i++ ) {
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

		  	pthread_mutex_unlock (&S_Three);
		  	cout << "third thread:" << endl;
	  		cout << array[0][0];
	  		cout << array[0][1];
	  		cout << array[0][2];
	  		cout << array[0][3];
	  		cout << array[0][4];
		}//for
		
	}//else
	

}//void



















