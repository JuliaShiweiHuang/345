/*
 * sumodd2.cpp
 * 
 * (Almost) final version of sum of odd values between 1 and max
 */
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

struct storestuff {
   int half;              // which half the process is computing
   int sum;               // sum of that half
   int max;               // max value
};
void * add_values(void *);

int main() {
     pthread_t thread1, thread2;   // two threads
     int half1, half2;             // identify which half of list each
                                   // thread will compute
     int final_sum;                // final sum of both threads
     struct storestuff * ptr;

     cout << "Enter max: ";
     ptr = new storestuff;
     cin >> ptr->max;

     ptr->half = 1;
     pthread_create (&thread1, NULL, add_values, (void *) ptr);
                    
     ptr->half = 2;
     pthread_create (&thread2, NULL, add_values, (void *) ptr);

     // must wait for children to finish before displaying sum!
     pthread_join (thread1, NULL);  // wait for thread1 to finish
     cout << "sum from thread1: " << ptr->sum << endl;
     final_sum = ptr->sum;

     pthread_join (thread2, NULL);  // wait for thread2 to finish
     cout << "sum from thread2: " << ptr->sum << endl;
     final_sum += ptr->sum;

     cout << "Sum: " << final_sum <<  endl;
     return 0;
  }
  
// separate threads!
void * add_values(void * ptr) {
     struct storestuff * local_ptr = (struct storestuff *) ptr;
     int half = local_ptr->half;
     int mymin, mymax;
     int max = local_ptr->max;

     local_ptr->sum = 0;
     // find min and max for this process
     if (half == 1) {
        mymin = 1;
        mymax = max / 2;
     } else {
        mymin = max / 2 + 1;
        if (!(mymin % 2))
           mymin++;
        mymax = max;
     }
     while (mymin <= mymax) {
        local_ptr->sum += mymin;
        mymin += 2;
     }
  }