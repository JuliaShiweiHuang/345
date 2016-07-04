/* 
 * threads1.cpp
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

void* print_message_function( void *ptr ); 
  
int main()
{
   pthread_t thread1, thread2;
   char message1 [6] = "Hello";
   char message2 [6] = "World";
   cout << "this is thread1 even though I don't know what the hell is going on" << thread1 << endl;
   cout << "this is thread2 even though I don't know what the hell is going on" << thread2 << endl;
   cout << "This process is ??? As I am printing the process ID: " << getpid() << endl;
   pthread_create(&thread1, NULL, print_message_function, (void*) message1);
   cout << "this is message1" << message1 << endl;
   // cout << "this is message1[6] " << message1 [6] << endl;
   // cout << "this is message2" << message2 << endl;




}

void *print_message_function(void *ptr) {
	char*message;
	message = (char*) ptr;
	cout <<"this is just to test whether the void function message can be printed: " << message << endl;
}