#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <unistd.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <iomanip>


using namespace std;

//const global
const int MEMORY_SIZE = 1048576;
//global int;
int totalSize = 0;
int skipJob = 0;

struct job {
	char op;
	int PID;
	int size;
	bool hasWrittenInMemoryBlock;
	bool hasNotPreviouslyBeenPushedInVector;
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
		vector <int>::iterator intVecIter; //in order to use insert function;
		job thisJob;
		size_t vectorSize;
		bool hasFreeMemoryBlock = false;
		// char fop; int fPID, fsize;
		myFile >> thisJob.op;

		while ( thisJob.op != 'Q') {
			myFile >> thisJob.PID;
			if ( thisJob.op == 'A') {
				//this should be calling allocate memory function;
				myFile >> thisJob.size;
				// thisJob.hasWrittenInMemoryBlock = false;
				totalSize = totalSize + thisJob.size;
				

				if ( totalSize <= MEMORY_SIZE ) {
					thisJob.hasNotPreviouslyBeenPushedInVector = true;
					if ( hasFreeMemoryBlock == true ) { // need debug: if there are any free memory chunk; or if there are any memory chunk;
						//add statement, if the -1 mark is marked contigiously
												//combine these spaces together;
						//search the whole vector to see memory blocks;
						for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
							if (memoryCalculator[i].PID == -1) {// if there are memory chunks/ there is memory chunk;
								if (thisJob.size <= memoryCalculator[i].size) {// if this job size is less or equal than the earliest memory chunk;
									//begin inserting;
									memoryCalculator.insert(memoryCalculator.begin()+i, thisJob);//insert at position 2 for D3 statement;
									thisJob.hasNotPreviouslyBeenPushedInVector = false;
									//change the memory size for that memory chunk;
									memoryCalculator[i+1].size = memoryCalculator[i+1].size - thisJob.size;
									// memoryCalculator[memoryCalculator.begin()+i+1].size -= thisJob.size;
									totalSize = totalSize - thisJob.size;
									break;
								}


								// else { //the job size is larger than all the memory chunk;
								// 	memoryCalculator.push_back(thisJob);//push this job at the back of the vector
								// 	thisJob.hasNotPreviouslyBeenPushedInVector = false;
								// 	cout << "80" << endl;
								// }

					    	}//if;
						}//for
						
					}
					// else {// if there arn't any free memory chunk OR memory chunk is less than PID size; OR this job hasn't been pushed before;
						// if ( !thisJob.hasNotPreviouslyBeenPushedInVector ) {
						if ( thisJob.hasNotPreviouslyBeenPushedInVector == true ) {
							memoryCalculator.push_back(thisJob);
						}

					// }

				}
				else {//not enough memory size;
					skipJob ++; // in order to get status for number of processes that did not fit in memory;
					//delete the total memory with that PID number;
					totalSize = totalSize - thisJob.size;
					// somehow need to track with their PID;
					cout << "PID " << thisJob.PID << " is skipped." << endl;
				}
				

			}
			else {//op == 'D'
				//this should be calling deallocate memory function;
				// cout <<"debug" << endl;
				// cout << thisJob.PID << endl;
				// memoryCalculator.erase(memoryCalculator.begin() + thisJob.PID - 1);//erase the thisJob th element; //hopefully only erase op;
				memoryCalculator[thisJob.PID - 1].PID = -1;
				memoryCalculator[thisJob.PID -1].op = 'D';
				hasFreeMemoryBlock = true;
				// cout << memoryCalculator[thisJob.PID -1].size <<  endl;//this will give me 90000;
				// memoryCalculator[thisJob.PID - 1].PID = -1;

			}
			myFile >> thisJob.op;
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











