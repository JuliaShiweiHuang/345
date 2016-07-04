/* 
 * fork2.cpp
 *
 * Purpose: Find sum of odd numbers up to max value
 * Input  : Integer max
 * Output : Sum of all the odd numbers
 */

#include <unistd.h>
#include <iostream>

using namespace std;
  
int main()
  {
     int child1, child2;   		// each child computes half
     int sum = 0;			// final sum
     int min_child1, min_child2;	// min values for each child
     int max_child1, max_child2;	// max values for each child
     int child1_sum, child2_sum;	// sum for each child
     int num1, num2;			// current odd number for each child
     int max;				// max odd number

     child1_sum = child2_sum = 0;
     cout << "Enter max number: ";
     cin >> max;
     cin.get();			// what does this do?
     min_child1 = 1;		// child1 will compute sum of lower half
     max_child1 = max / 2;	
     min_child2 = max / 2 + 1; 	// child2 will compute sum of upper half
     max_child2 = max;

     child1 = fork();   
     if (child1 == -1) {
        cout << "Fork failed for PID " << getpid() << endl;
        return -1;
     }

     if (child1 == 0) {
        // This is child1; compute from min_child1 to max_child1
        child1_sum = 0;
        num1 = min_child1;
        while (num1 <= max_child1) {
           child1_sum += num1;
           num1 += 2;
        }
        cout << "Child 1 sum: " << child1_sum << endl;

     } else {
        // This is the parent; spawn another child to do the upper half
        child2 = fork();
        if (child2 == -1) {
           cout << "Fork failed for PID " << getpid() << endl;
           return -1;
        }

        if (child2 == 0) {
           // Yep, this is child2; compute from min_child2 to max_child2
           child2_sum = 0;
           // check if first value is odd
           if (min_child2 % 2)
              num2 = min_child2;
           else
              num2 = min_child2 + 1;

           while (num2 <= max_child2) {
              child2_sum += num2;
              num2 += 2;
           }
           cout << "Child 2 sum: " << child2_sum << endl;
         } else {
            // Still the parent; just wait around...
         }

     }
     // Combine answers...
     sum = child1_sum + child2_sum;
     cout << "Sum is: " << sum << endl; // parent doesn't know anything. Thus the sum = 0;
     
     return 0;
}