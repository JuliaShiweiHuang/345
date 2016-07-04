#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;

struct referenceArray {
	long group;
	long *arrayPointer;
};

void * organizeArray ( void * );


int main () {

	
	
	pthread_t thread1, thread2, thread3;
	long group1, group2, group3;


	pthread_mutex_init(&S_One, NULL);
	pthread_mutex_init(&S_Two, NULL);
	pthread_mutex_init(&S_Three, NULL);

//Not sure about this step;
	pthread_mutex_lock(&S_Two);
	pthread_mutex_lock(&S_Three);

	group1 = 1;
	pthread_create (&thread1, NULL, organizeArray, (void *) group1);

	group2 = 2;
	pthread_create (&thread1, NULL, organizeArray, (void *) group2);

	group3 = 3;
	pthread_create (&thread1, NULL, organizeArray, (void *) group3);


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);

	cout << "main(){} done." << endl;

	return 0;

}


void * organizeArray ( void* ptr) {

	ifstream file ("smalltest.txt");
	char character;
	char array[200][60];
	long row = 0, col = 0;
	//initialize array;
	for ( long row = 0; row < 200; row ++ ) {
		for ( long col = 0; col < 60; col ++ ) {
			array[row][col] = ' ';
		}
	}

	long someNum = (long) ptr;
	cout << "Debug: In thread, someNum = " << someNum << endl;

	if ( someNum == 1 ) {
		row = 0;
		col = 0;
		// pthread_mutex_lock (&S_One);
		// pthread_mutex_lock (&S_Two);
		// pthread_mutex_lock (&S_Three);
		
		if ( file.is_open() ) { //if I could locate my file;
			while ( file.get(character) ) {
				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {
					pthread_mutex_unlock (&S_Two);

					row ++;
					col = 0;
				}//if
			}//while
			cout << "Debug: someNum == 1" << endl;
		}//if
		

	}//if
	else if ( someNum == 2 ){
		pthread_mutex_lock (&S_Two);
		cout << "Debug: someNum == 2" << endl;
		pthread_mutex_unlock (&S_Three);
	}
	else { //someNum == 3
		pthread_mutex_lock (&S_Three);
		cout << "Debug: someNum == 3" << endl;
		pthread_mutex_unlock (&S_One);
	}

	

	// if ( someNum == 1 ) {
	// 	while ( file.get(character) ) {
	// 		array[row][col] = character;
	// 		col ++;
	// 		if ( character == '\n' ) {
	// 			pthread_mutex_unlock(&S_Two);
	// 			pthread_mutex_lock(&S_One);
	// 			row ++;
	// 			col = 0;
	// 		}//if
	// 	}//while;
	// }

	// cout << "array row and col" << array[0][0] << endl;
	// cout << array[0][1];
	// cout << array[0][2];
	// cout << array[0][3];



}



















