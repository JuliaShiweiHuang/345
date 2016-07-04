/* 
 * threads2.cpp
 *
 * Purpose: Display "hello world" message using separate threads
 * Input  : None
 * Output : "Hello World" ... or is it?
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main () {
	pthread_t thread1, thread2;
	char message1 [6] = "Hello";
	cout << "process id" << getpid() << endl;
	
}