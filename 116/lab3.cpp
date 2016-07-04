// Developer: Shiwei Huang
// Due: Sunday, Sep 20th, 2015;
// Purpose: C++ 116 Wrap up; Next class starts Algorithms; Review how queues are implemented and how to traverse a linked list;
// Everything is public. In other words, nothing is private and nothing is protected;

// Queue: in the begining, First = NULL; Last = NULL; 


#include <iostream>
#include <stdlib.h>

using namespace std;

class intCell {
public:
	int value; //an integer called value;
	intCell *next; //a pointer to an intCell called next;
	intCell (int integer) { value = integer; next = NULL;}; //Use that integer to initialize the variable value;
	intCell (int, intCell* ); //This is my second constructor; tDoesn't matter if the input for constructors are the same because it's either constructor 1 or constructor 2;
	// operator overloading function;
};

intCell::intCell (int integer, intCell *pointer ) {
	value = integer;
	next = pointer;

}

class myIntQueueADT {
	virtual int firstVlue (); // Tell complier I will not give you the code of this function of this class; 
	virtual int enqueue (int );
	virtual void dequeue ();
	virtual int maxValue ();
	virtual void print ();
};

class llIntQueue : public myIntQueueADT {
	llIntQueue () {}; // Constructor;
};

int main () {
	intCell a(2);
	cout << "I am just testing my intell class " << a.value << endl;
}
