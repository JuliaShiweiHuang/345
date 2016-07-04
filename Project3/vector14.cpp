// Comments:
// In your spec sheet, you said "this program should be designed using OOP principles." I am not sure how strictly you defined as for
// OOP principles.

// Currently:
// 1. I am using <vector> from Standard Template Library. 
// However, my struct doesn't comtain any function but only members like op, PID, size etc.
// 2. I am not sure whether you are assuming that allocate and deallocate needs to be written as separate functions. 
// As for now while I am reading the file, I am allocating and deallocating my PID under my readFile function. 


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
// const int MEMORY_SIZE = 10000;
//global int;
int totalSize = 0;
int skipJob = 0;
int totalDeallocateProcesses = 0;

struct job {
	char op;
	int PID;
	int size;
	bool hasWrittenInMemoryBlock;
	bool hasNotPreviouslyBeenPushedInVector;
	int startAddress, endAddress;
// public:
	// job(){}; //default constructor;
	// job (string inFileName); //second constructor;
};

// job::job(string inFileName) { //second constructor
// 	fileName = inFileName;
// 	ifstream FIN;
// 	FIN.open(fileName);
// 	if (!(FIN.is_open())) {
// 		cout << "Sorry. Cannot Locate your file." << endl;
// 		FIN.close();
// 	}
// 	else {
// 		cout << "file is open" << endl;
// 	}
// }

vector<job> readFile(string inFileName) {
	ifstream FIN;
	FIN.open(inFileName);

	vector <job> memoryCalculator;
	job thisJob;
	size_t vectorSize;
	bool hasFreeMemoryBlock = false;
	FIN >> thisJob.op;

	while (thisJob.op != 'Q') {
		FIN >> thisJob.PID;
		if ( thisJob.op == 'A' ) {
			thisJob.hasNotPreviouslyBeenPushedInVector = true;
			FIN >> thisJob.size;
			if ( totalDeallocateProcesses == 0 ) {// no free memory available;
			 	totalSize = totalSize + thisJob.size;
			 	
			 	if ( totalSize <= MEMORY_SIZE ) {
			 		//add at the back;
			 		memoryCalculator.push_back(thisJob);
			 		thisJob.hasNotPreviouslyBeenPushedInVector = false;
			 	}//if
			 	else {// skip this job because there is not enough memory;
					skipJob ++; // in order to get status for number of processes that did not fit in memory;
					//delete the total memory with that PID number;
					// somehow need to track with their PID;
					totalSize = totalSize - thisJob.size;
					cout << "======================================" << endl;
					cout << "PID " << thisJob.PID << " is skipped." << endl;
					cout << "======================================" << endl;
			 	}
			}//if no free memory available;

			else {// there is free memory chunk available;

				// if this PID <= this memory chunk 
				// 	insert at that memory chunk;
				// else
				// 	insert at the back;

				// if this PID <= free memory; then push this PID at this free memory location;
			 	for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
					if (memoryCalculator[i].PID == -1) {// if there are memory chunks/ there is memory chunk;
						if (thisJob.size <= memoryCalculator[i].size) {// if this job size is less or equal than the earliest memory chunk;
							//begin inserting;
							memoryCalculator.insert(memoryCalculator.begin()+i, thisJob);//insert at position 2 for D3 statement;
							thisJob.hasNotPreviouslyBeenPushedInVector = false;
							//change the memory size for that memory chunk;
							memoryCalculator[i+1].size = memoryCalculator[i+1].size - thisJob.size;
							// memoryCalculator[memoryCalculator.begin()+i+1].size -= thisJob.size;
							break;
						}

				    }//if;    
				}//for

				// if after adding the new PID's size into the -1 memory chunk; I am deleating that free memory chunk;
				for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
					if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i].size == 0) ) {
						memoryCalculator.erase(memoryCalculator.begin()+i);
						totalDeallocateProcesses --;
					}//if
				}//for

				//meaning the memory chunk is less than this job; then I am pushing this job at the back;
				if (thisJob.hasNotPreviouslyBeenPushedInVector == true) {
					totalSize = totalSize + thisJob.size;
			 		if ( totalSize <= MEMORY_SIZE ) {
			 			memoryCalculator.push_back(thisJob);//push this job at the back of the vector
						thisJob.hasNotPreviouslyBeenPushedInVector = false;
			 		}
			 		else {
			 			skipJob ++; // in order to get status for number of processes that did not fit in memory;
						//delete the total memory with that PID number;
						// somehow need to track with their PID;
						totalSize = totalSize - thisJob.size;
						cout << "======================================" << endl;
						cout << " PID " << thisJob.PID << " is skipped." << endl;
						cout << "======================================" << endl;
			 		}//else
			 	}//if;


			}//else

		}//if thisJob.op == 'A'

		else {//op == 'D'
			// note: should deallocate by PID not by the memoryCalculator vector position
			//this should be calling deallocate memory function;
			// cout << thisJob.PID << endl;
			// memoryCalculator.erase(memoryCalculator.begin() + thisJob.PID - 1);//erase the thisJob th element; //hopefully only erase op;
			for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
				if (memoryCalculator[i].PID == thisJob.PID ) {
					memoryCalculator[i].PID = -1;
					memoryCalculator[i].op = 'D';
					hasFreeMemoryBlock = true;
					totalDeallocateProcesses ++;
					break;
				}

			}

			for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i) {
				if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i+1].PID == -1) ) {
					memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
					memoryCalculator.erase(memoryCalculator.begin() + i + 1);
					totalDeallocateProcesses --;
					i--;
				}//if	
			}//for

		}//else op == 'D'

		FIN >> thisJob.op;
	}//while

	FIN.close();
	
	return memoryCalculator;

}

void printStatus(vector<job> memoryCalculator) {

	cout << " " << endl;
	cout << " " << endl;
	//output table part

	memoryCalculator[0].startAddress = 0;
	memoryCalculator[0].endAddress = memoryCalculator[0].size - 1;
	cout << setw(23) << "Memory Table" << endl;	
	cout << "======================================" << endl;
	cout << setw(4) << "PID" << setw(10) << "Start" << setw(10) <<"End" << setw(10) << "Size" << endl;
    cout << setw(4) << memoryCalculator[0].PID << setw(10);
    cout << memoryCalculator[0].startAddress << setw(10);
	cout << memoryCalculator[0].endAddress << setw(10);
	cout << memoryCalculator[0].size << setw(10) << endl;


	int maxNumberOfProcessInVector;
    for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		memoryCalculator[i].startAddress = memoryCalculator[i-1].endAddress + 1;
		memoryCalculator[i].endAddress = memoryCalculator[i].startAddress + memoryCalculator[i].size - 1;
		cout << setw(4) << memoryCalculator[i].PID << setw(10);
		cout << memoryCalculator[i].startAddress << setw(10);
		cout << memoryCalculator[i].endAddress << setw(10);
		cout << memoryCalculator[i].size << setw(10) << endl;
		maxNumberOfProcessInVector = i;
	}

	// if not used free memory, cout PID == -1;
	// else don't see out any free memory;
	cout << setw(4) << -1 << setw(10);
	cout << memoryCalculator[maxNumberOfProcessInVector].endAddress + 1 << setw(10); // Free remaining memory startaddress
	cout << MEMORY_SIZE << setw(10);
	int lastMemoryChunkSize = MEMORY_SIZE - (memoryCalculator[maxNumberOfProcessInVector].endAddress + 1) + 1;
	cout << lastMemoryChunkSize << setw(10) << endl;	

	cout << "======================================" << endl;
	
	cout << "Number of processes that is skipped is: " << skipJob << endl;

	// calculate total amount of memory in use at the end of the simulation;
	int memoryInUse = 0;
	for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		if (memoryCalculator[i].PID != -1) {
			// cout << memoryCalculator[i].size << endl;
			memoryInUse = memoryCalculator[i].size + memoryInUse;
		}
	}//for
	memoryInUse += memoryCalculator[0].size;
	cout << "Total amount of memory in use at the end of the simulation is: " << memoryInUse << " bytes."<< endl;

	//calculate total amount of memory remaining
	int memoryRemaining = 0;
	for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		if (memoryCalculator[i].PID == -1) {
			// cout << memoryCalculator[i].size << endl;
			memoryRemaining = memoryCalculator[i].size + memoryRemaining;
		}
	}//for
	memoryRemaining += lastMemoryChunkSize; //also need to add on the last memory chunk size;
	cout << "Total amount of memory remaining is: " << memoryRemaining << " bytes."<< endl;

	//print of number of memory blocks left
	totalDeallocateProcesses += 1; // add one because I also need to count the free space left in the end;
	cout << "Number of contiguous spaces (memory blocks) remaining is: " << totalDeallocateProcesses << endl;

	float memoryBlockAverageSize = (float) memoryRemaining / (float)totalDeallocateProcesses;
	cout << "Average size of remaining memory blocks is: " << memoryBlockAverageSize << " bytes."<< endl;




}


int main () {
	int fileNumber;
	string fileName;
	cout << "Type in the name of the input file: " << endl;
	cin >> fileName;
	vector<job> memoryCalculator = readFile(fileName);
	printStatus(memoryCalculator);
	// delete vector<job> memoryCalculator;
	// printStatus();
	// job myJob = job(fileName);
	return 0;
	// ifstream myFile (fileName);
	// ifstream myFile ("file.txt");



}












