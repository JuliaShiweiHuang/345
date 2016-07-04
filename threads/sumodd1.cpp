/* 
 * Joe J. Schmoe
 *
 * summodd1.cpp 
 *
 * Purpose:  Find sum of odd integer values between 1 and max
 * Input  :  Max value (integer)
 * Output :  Sum of odd integers
 */

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void * add_values(void *);  

int global_max;      // shows how threads have access to global variables
int global_sum = 0;  // sum of values
  
int main()
  {
     pthread_t thread1, thread2;   // two processes
     int half1, half2;             // identify which half of list each
                                   // process will compute

     cout << "Enter max: ";
     cin >> global_max;

     half1 = 1;
     pthread_create( &thread1, NULL,
                    add_values, (void *) half1);
     half2 = 2;
     pthread_create(&thread2, NULL,
                    add_values, (void *) half2);







     cout << "Sum: " << global_sum << endl;
     return 0;
  }
  
// separate threads!
void * add_values(void * temp)
  {
     int half = (int) temp;  // simply copying makes this pass by value
     int min, max;

     // find min and max for this process
     if (half == 1) {
        min = 1;
        max = global_max / 2;
     } else {
        min = global_max / 2 + 1;
        if (!(min % 2))
           min++;
        max = global_max;
     }

     while (min <= max) {
        // cout << "adding: " <<  min << endl;   // debug
        global_sum += min;    
        min += 2;
     }
     // cout << getpid() << " sum " << global_sum << endl;   // debug
  }