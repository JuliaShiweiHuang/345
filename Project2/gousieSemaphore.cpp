/*
 * semaphore.cpp
 *
 * Very simple example of the use of a semaphore
 * Thread 1 sums values from 1 to 4000, thread 2 sums 4001 to 8000, both
 * using the global "sum" variable.
 */ 

#include<iostream>
#include<pthread.h>

using namespace std;

pthread_mutex_t S;	// semaphore

void * addvals (void *);

long sum = 0;		// global sum - shared resource

int main ()
{
   pthread_t thread1, thread2;      // two processes
   int group1, group2;

   pthread_mutex_init (&S, NULL);   // set up semaphore

   group1 = 1;
   pthread_create (&thread1, NULL, addvals, (void *) group1);
   group2 = 2;
   pthread_create (&thread2, NULL, addvals, (void *) group2);
   pthread_join (thread1, NULL);  // wait for thread1 to finish
   pthread_join (thread2, NULL);  // wait for thread2 to finish

   pthread_mutex_destroy (&S);    // deallocate semaphore

   cout << "Sum is " << sum << endl;

   return 0;
}


void * addvals (void* ptr)
{
   int i, start;
   int whoami = (int) ptr;

   if (whoami == 1) 
      start = 1;
   else 
      start = 4001;

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