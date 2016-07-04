#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <math.h>
#include <vector>

using namespace std;

struct job {
	int PID, size;
};

//global constant;
const int MEMORY_SIZE = 1048576;
// global memory counter;
int totalSize = 0;

void memoryCalculation() {//read from file
	vector <job> jobVector;
	char op;
	int PID, size;
	cin.get(op);
	while ( op != 'Q' ) {
		cin >> PID;
		if ( op == 'A' ) {
			cin >> size;
			totalSize = size + totalSize;

		}
		else { //op == 'D'

		}
	}



}

struct Something{
    int x;
    int y;
};
int main()
{  
    vector <Something> v;
    int x, y;
    cin >> x >> y;
    v.push_back(x, y);
}