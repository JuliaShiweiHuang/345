// fork1.cpp - simplest possible fork(ing) program

#include <unistd.h>     // needed for fork()
#include <iostream>

using namespace std;

int main()
  {
     int childnum;

     // Getpid() returns the process ID of the calling process.  The ID is guar-
     // anteed to be unique and is useful for constructing temporary file names.

     // Getppid() returns the process ID of the parent of the calling process.


     cout << "PID (process ID of the calling process): " << getpid()  <<  endl;
     // The child gets a return code of 0, and the child's PID is returned
     // to the parent.  A -1 is returned if the fork fails.  Read that again.
     // We can then use childnum to differentiate between the parent and
     cout << "getppid(): (process ID of the parent of the calling process)" << getppid() << endl;
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
        cout << "parent PID: " << getppid() << endl;
     }
     // sleep(1);
     return 0;
}