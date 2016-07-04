#include <iostream>
#include <vector>
#include <string> 

using namespace std;

struct job {
	char op;
	int PID, size;
};


int main () {
	vector<job> x;
	job thisJob;
	size_t vectorSize;

	thisJob.op = 'A';
	thisJob.PID = 1;
	thisJob.size = 200000;

	for ( int i = 0, vectorSize = x.size(); i < vectorSize; ++i ) {
		cout << x[i].op << endl;
		cout << x[i].PID << endl;
		cout << x[i].size << endl;
	}

}