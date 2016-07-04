// fork1.cpp - simplest possible fork(ing) program

#include <unistd.h>     // needed for fork()
#include <iostream>    // std::cin, std::cout
#include <fstream> 

using namespace std;

int main()
  {
     int childnum;

     cout << "PID: " << getpid() << endl;
     // The child gets a return code of 0, and the child's PID is returned
     // to the parent.  A -1 is returned if the fork fails.  Read that again.
     // We can then use childnum to differentiate between the parent and
     // the child.
     childnum = fork();  

     // at this point, TWO PROCESSES are running!
     cout << "childnum : " << childnum << endl;
     if (childnum == -1) {
        cout << "Fork failed for PID " << getpid() << endl;
        return -1;
     }
     
     if (childnum == 0) {
        // This is the child running
        cout << "child PID: " << getpid() << "; parent PID: " << getppid() << endl;
     } else {
        // This is the parent running
        cout << "parent PID: " << getpid() << endl;
     }

     //cin.get(); // This line wont stop parent ID. 
     
     return 0;
}