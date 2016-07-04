#include<iostream>
#include<pthread.h>

using namespace std;

void * printvals (void *);

int main ()
{
   pthread_t thread1, thread2;    // two threads
   long odd, even;

   odd = 0;
   pthread_create (&thread1, NULL, printvals, (void *) odd);
   even = 1;
   pthread_create (&thread2, NULL, printvals, (void *) even);
   // pthread_join (thread1, NULL);  // wait for thread1 to finish
   // pthread_join (thread2, NULL);  // wait for thread2 to finish

   cout << endl << "Done" << endl;

   return 0;
}


void * printvals (void* ptr)
{
   long i;
   long min, max;
   long even = (long) ptr;

   cout << "in thread, even = " << even << endl;

   if (even) {
      max = 20;
      min = 0;
   } else {
      max = 19;
      min = 1;
   }

   for (i = min; i <= max; i+=2)
      cout << i << " ";
   cout << endl;
}