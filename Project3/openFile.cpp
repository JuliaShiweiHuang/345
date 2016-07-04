#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <math.h>
#include <vector>

using namespace std;

//const global
const int MEMORY_SIZE = 1048576;
//global int;
int totalSize = 0;

struct job {
	char op;
	int PID;
	int size;
};

int main () {
	int fileNumber;
	string fileName;
	// cout << "Type in the name of the input file: " << endl;
	// cin >> fileName;
	// ifstream myFile (fileName);
	ifstream myFile ("file.txt");
	int fPID, fsize; char fop;
	//this should be calling the file open function;
	if ( myFile.is_open() ) {
		vector <job> memoryCalculator;
		job thisJob;
		size_t vectorSize;
		myFile >> fop;

		thisJob.op = fop;
		// debug statement
		while ( thisJob.op != 'Q') {
			myFile >> fPID;
			thisJob.PID = fPID;
			if ( thisJob.PID == 'A') {
				//this should be calling allocate memory function;
				myFile >> fsize;
				thisJob.size = fsize;
				totalSize = totalSize + fsize;

				if ( totalSize < MEMORY_SIZE ) {
					bool hasWrittenInMemoryBlock = false;


				}




			}
			else {//op == 'D'
				//this should be calling deallocate memory function;
			}
			myFile >> fop;
		}
		myFile.close();
	}
	else {
		cout << "Sorry. Cannot locate your file." << endl;
	}
	cout << "total size is: " << totalSize << endl;

}