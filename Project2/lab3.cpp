// Last edit: 10/03/2015 20:50 UNFINISHED BUT WORKING VERSION. Operator overloading has not finished yet. 
// Developer: Shiwei Huang
// Purpose: C++ 116 Wrap up; Review how queues are implemented and how to traverse a linked list;
// Note: without main, everything compiles. However, it doesn't compile when executing "llIntQueue one;"


#include <iostream>
#include <stdlib.h>

using namespace std;

class intCell {
    
public:
	int value; //an integer called value;
	intCell *next; //a pointer to an intCell called next;
	intCell(){};
	intCell (int integer) { value = integer; next = NULL;};
	//This is my second constructor; Doesn't matter if the input for constructors are the same because it's either constructor 1 or constructor 2;
	intCell (int integer, intCell *pointer ) { value = integer; next = pointer;};
 // operator overloading function;
	intCell operator+ ( intCell intCellB) {
		intCell ans;
		ans.value = value + intCellB.value;
		ans.next = NULL; 
		return ans;
	}
};

class myIntQueueADT {
public: 
	//Note: For pure virtual functions; do not have to implement the actual function;
	// this will be defined later;
	virtual int firstValue () = 0; // Tell complier I will not give you the code of this function of this class; 
	virtual void enqueue (int ) = 0;
	virtual void dequeue () = 0;
	virtual int maxValue () = 0;
	virtual void print () = 0;
	myIntQueueADT operator+ ( llIntQueue ) {
		myIntQueueADT newQueue;
		/* QUESTION */
		/* QUESTION */
		/* QUESTION */
		/* QUESTION */
		/* QUESTION */

	}
};

// cerate a class llIntQueue that is derived from myIntQueueADT;
class llIntQueue:public myIntQueueADT {
public:
	intCell *first, *last; //two pointers to intCell: first and last;
	llIntQueue () { first = NULL; last = NULL; }; // Constructor;
	int firstValue () { return first -> value; }; // QUESTION
	void enqueue (int);
	void dequeue ();
	int maxValue ();
	void print ();
};

void llIntQueue::enqueue (int num) { //function enqueue method;
	intCell *newCell;
	newCell = new intCell;
	newCell -> value = num;
	newCell -> next = NULL;

	if ( first == NULL ) { //If initially queue is empty;
		first = newCell;
		/********* QUESTION **********/
		last = newCell; //QUESTION: I COPIED THIS LINE OF CODE FROM BOOK P1125. BUT WHY???
	}
	else { //Add newCell at read;
		last -> next = newCell;
		last = last -> next;
	}
} //end enqueue;

void llIntQueue::dequeue () {
	intCell *temp;
	if ( first != NULL ) {
		temp = first;
		first = first -> next;
		delete temp; //delete first node;
		if ( first == NULL ) { //after deletion, queue is empty;
			last = NULL;
		} //if
	} //if
	else { //current queue is empty;
		cout << "Current queue is empty." << endl;
	}
}

//returns the max value contained in queue (while traversing the linked list);
int llIntQueue::maxValue () {
	intCell *current;
	current = first;
	int max;
	max = current -> value;
	while ( current != NULL ) {
		if ( current -> value > max ) {
			max = current -> value;
		}
		current = current -> next;
	}
	return max;
}

void llIntQueue::print () {
	intCell *current;
	current = first;
	while ( current != NULL ) {
		cout << current -> value << " "; //all these integers should be on the same line, separated by spaces;
		current = current -> next; 
	} //while;
}


int main () {

	llIntQueue one, two, three;
	myIntQueueADT *pointer;
	cout << "Please type 10 integers that you want to put in your first queue." << endl;
	int integers;
	for ( int i = 0; i < 10; i++ ) {
		cin >> integers;
		one.enqueue (integers);
	}

	int maximumValueFromllIntQueueOne = one.maxValue();
	cout << "Thus, the maximum value from llIntQueue One is: " << maximumValueFromllIntQueueOne << endl;
	

	cout << " " << endl; 
	cout << "Now let's fill up the second queue: " << endl;
	cout << "Please type 10 integers that you want to put in your second queue." << endl;
	cout << " " << endl; 

	for ( int i = 0; i < 10; i++ ) {
		cin >> integers;
		two.enqueue (integers);
	}


	int maximumValueFromllIntQueueTwo = two.maxValue();
	cout << "Thus, ths maximum value from llIntQueue Two is: " << maximumValueFromllIntQueueTwo << endl;



	return 0;


}














