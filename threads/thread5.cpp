#include <iostream>
#include <pthread.h>
using namespace std;

void *print_message(void*){

    cout << "Threading\n";
}



int main() {

    pthread_t t1;

    pthread_create(&t1, NULL, &print_message, NULL);
    cout << "Hello" << endl;
    cout << endl;
    return 0;
}