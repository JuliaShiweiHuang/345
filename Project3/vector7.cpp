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
	// bool 
};

int main () {
	int fileNumber;
	string fileName;
	// cout << "Type in the name of the input file: " << endl;
	// cin >> fileName;
	// ifstream myFile (fileName);
	ifstream myFile ("file.txt");

	//this should be calling the file open function;
	if ( myFile.is_open() ) {
		vector <job> memoryCalculator;
		job thisJob;
		size_t vectorSize;
		char fop; int fPID, fsize;
		myFile >> fop;
		thisJob.op = fop;

		while ( fop != 'Q') {
			myFile >> fPID;
			cout << fPID << endl;
			thisJob.PID = fPID;
			if ( thisJob.op == 'A') {
				//this should be calling allocate memory function;
				myFile >> fsize;
				cout << fsize << endl;
				thisJob.size = fsize;
				totalSize = totalSize + fsize;

				// if ( totalSize < MEMORY_SIZE ) {
				// 	bool hasWrittenInMemoryBlock = false;


				// }
				memoryCalculator.push_back(thisJob);



			}
			else {//op == 'D'
				//this should be calling deallocate memory function;
			}
			myFile >> fop;
			cout << fop << endl;
			thisJob.op = fop;
		}//while;

		// this is just debugging statement to make sure my vector called memoryCalculator is working properly;
		for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
			cout << "\tOP: " << memoryCalculator[i].op << " ";
	        cout << "\tPID: " << memoryCalculator[i].PID <<" ";
	        cout << "\tSize: " << memoryCalculator[i].size << endl;
		}

		myFile.close();
	

	}
	else {
		cout << "Sorry. Cannot locate your file." << endl;
	}
	cout << "total size is: " << totalSize << endl;
	

}











