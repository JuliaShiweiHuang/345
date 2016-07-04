//#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;

void *print_message(void*){

    cout << "Threading\n";
}



int main() {

    pthread_t t1;
    //cout << "I assume this is this time process ID: " << getpid() << endl;
    cout << "I assume this is threads ID" << t1 << endl;
    pthread_create(&t1, NULL, &print_message, NULL);
    cout << "Hello" << endl;
    cout << " " << endl;

    return 0;
}