#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

pthread_mutex_t semaphore;  // semaphore

void *doStuff (void *);
long x = 13;

int main () {

	pthread_t thread1, thread2;
	int pid;
   
	pid = 1;
	pthread_create (&thread1, NULL, doStuff, (void *) pid);

	pid = 2;
	pthread_create(&thread2, NULL, doStuff, (void *) pid );

	
	cout << "Kenny's dead now, and x = " << x << endl;

	 return 0;
	
}


void *doStuff (void *ptr) {

	long num = (long) ptr;

	if (num == 1) {
		x = x + 4;
		cout << "My name is Kenny, and x = " << x << endl;
	}

	else {
		x = x * 4;
		cout << "My name is Cartman, and x = " << x << endl;
	}
	
}




