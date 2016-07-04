#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>

using namespace std;

pthread_mutex_t S;	// semaphore

void * addvals (void *);

int main () {
   pthread_t thread1, thread2, thread3; // three processes
   int group1, group2, group3;

   pthread_mutex_init (&S, NULL); // set up semaphore

   group1 = 1;
   pthread_create (&thread1, NULL, addvals, (void *) group1);
   group2 = 2;
   pthread_create (&thread2, NULL, addvals, (void *) group2);
   group1 = 3;
   pthread_create (&thread1, NULL, addvals, (void *) group3);

   pthread_join (thread1, NULL);  // wait for thread1 to finish
   pthread_join (thread2, NULL);  // wait for thread2 to finish
   pthread_join (thread3, NULL);  // wait for thread3 to finish

   pthread_mutex_destroy (&S);    // deallocate semaphore

   cout << " " << endl;

   return 0;
}


void * addvals (void* ptr) {

   int i, start;
   int threadArrivedFirst = (int) ptr;

   if ( threadArrivedFirst == 1 ) 
      start = 1;
      ifstream file ( "testSlash.txt" );
      char character;
      char array[200][60];
      int 

   else if
      start = 4001;

   else


   for (i = start; i <= start+3999; i++) {
         pthread_mutex_lock (&S);    // I want it!             (wait (S))
         sum += i;                   // critical region
         pthread_mutex_unlock (&S);  // You can have it now!   (signal (S))
   
         // take comments out below if you want to see interleaving of threads
         // (you may have to add larger numbers)
         // if (start == 1) cout << "thread 1" << endl;
         // else cout << "thread 2" << endl;

   }
}