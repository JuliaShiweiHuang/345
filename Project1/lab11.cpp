#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>

using namespace std;

//MY STRUCT
template <class Type>
struct NODE
{
	Type info;
	NODE<Type> *link;
};

//TEMPLATE QUEUE CLASS
template <class Type>
class Queue
{
public:
	Queue();
	bool isEmpty();
	void Enqueue(Type&);
	Type Front();
	void Dequeue();
private:
	NODE<Type> *front;

};

//CONSTRUCTOR
template <class Type>
Queue<Type>::Queue()
{
	front = NULL;
}

template <class Type>
bool Queue<Type>::isEmpty()
{
	return (front == NULL);
}

template <class Type>
void Queue<Type>::Enqueue(Type& passenger)
{
	NODE<Type> *newNODE;
	NODE<Type> *current = front;

	newNODE = new NODE<Type>;

	newNODE -> info = passenger;
	newNODE -> link = NULL;

	if (isEmpty())
	{	
		front = newNODE;
	}

	else
	{	
		while (current -> link != NULL)
		{
			current = current -> link;	
		}
		
		current -> link = newNODE;
	}
}

template <class Type>
Type Queue<Type>::Front()
{	
	
	return front -> info;
}

template <class Type>
void Queue<Type>::Dequeue()
{
	NODE<Type> *temp;
	
	temp = front;
	front = front -> link;
	delete temp;
}

//SUBWAY LINKED LIST
int main ()
{
	Queue<int> passengers;
	int num = 0;
	int count;

	while (num >= 0)
	{	
		cout << "Enter integer: " << endl;
		cin >> num;
		
		if (num > 0)
		{	
			passengers.Enqueue(num);
		}

		if (num == 0)
		{
			count = 0;
			while (count <= 5 && !passengers.isEmpty())		
			{					
				cout << passengers.Front() << " ";				
				passengers.Dequeue();			
				count++;
			}
		}
	}		
			
	
		
	
}