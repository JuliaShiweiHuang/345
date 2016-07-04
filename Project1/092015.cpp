#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct file {
    int MAXINT;
    int nextInt;
    int half;
};

void *bubble_sort (void *);

int main () {
    pthread_t thread1, thread2;
    int MAXINT;
    struct file *ptr1, *ptr2;
    ptr1 = new file;
    ptr2 = new file;
    ifstream openFile ("number.txt");
    if ( openFile.is_open() ) {
        file >> nextInt;
        ptr1 -> MAXINT = nextInt / 2;
        ptr2 -> MAXINT = nextInt - nextInt/2;
        ptr1 -> half = 1;
        pthread_create ( &thread1, NULL, bubble_sort, ( void *) ptr1 );
        ptr2 -> half = 2;
        pthread_create ( &thread2, NULL, bubble_sort, ( void *) ptr2 );
        
//      !!!!  STILL NEED TO FINISH THE REST OF THE PROGRAM !!!!
        ofstream myFileSum;
        pthread_join (thread1, NULL);
        // MERGE TWO ARRAY INTO ONE ARRAY;
//        http://stackoverflow.com/questions/12791266/c-concatenate-two-int-arrays-into-one-larger-array
        pthread_join (thread2, NULL);
        
        // BUBBLESORT THE BIG ARRAY;
        
    }
    else {//cannot open file;
        cout << "Sorry, cannot find your file" << endl;
    }

    return 0;
} //main;

//separate threads;
void *bubble_sort ( void *ptr ) {

    int half = local_ptr -> half;
    int MAXINT = local_ptr -> MAXINT;

    if ( half = 1 ) { // thread 1;
        myMax = MAXINT / 2;
        for ( int i = 0; i < myMax; ++i ) {
            file >> nextInt; // STILL NEED TO DEFINE nextInt;
            myArray [i] = nextInt;
        }
    } else { //thread 2;
        myMax = MAXINT - myMax;
        for ( int i = 0; i < myMax; ++i ) {
            file >> nextInt; //skip the first half of the file;
        }
        for ( int i = 0; i < myMAX; ++i ) {
            file >> nextInt;
            myArray[i] = nextInt;
        }
    }
    //starting bubbleSort;
    for ( int iteration = 1; iteration < myMax; iteration++ ) {
        for ( int index = 0; index < myMax - iteration; index++ ) {
            if ( myArray[index] > myArray[index+1] ) {
                int temp = myArray[index];
                myArray[index] = myArray[index+1];
                myArray[index+1] = temp;
            } //if
        } //for
    } //for
    
    //Write sorted array into file pending on thread1, thread2;
    ofstream myFile1, myFile2;
    if ( half = 1 ) {
        myFile1.open ("answerPart1.txt");
        for ( int i = 0; i < myMAX; ++i ) {
            myFile1 << myArray[i] << endl;
        }
        myFile1.close();
    }
    else { //half = 2;
        myFile2.open ("answerPart2.txt");
        for ( int i = 0; i < MAXINT - myMAX; ++i ) {
            myFile2 << myArray[i] << endl;
        }
        myFile2.close();
    }
    
} // bubbleSort;