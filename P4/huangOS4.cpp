/* Shiwei Huang
   CS345: OS4
   The purpose of the program: Implement the first-fit memory allocation scheme for the operating system.

   User Input: File name
   System Input: The file should contain any number of lines with the format of:
   				 <op> 	<PID>	<size>
   'A' or 'D' for allocate or deallocate, respectively;
   PID: process ID
   Size: size of the job in bytes
   'Q': indicates the end of the file

   Output:
   1. A table showing the final configuration of memory. Including PID, begin address, end address and size of its allocation.
   2. Number of processes (and their PIDs) that did not fit in memory.
   3. Total amount of memory remaining.
   4. Number of contiguous spaces (memory blocks) remaining
   5. Average size of remaining memory blocks

   Specifics:
   1. Currently, the size of main memory is 1M (2^20). However, processes can be any size. 
   2. The system has no garbage collection capabilities, aside from coalescing contiguous blocks when memory is deallocated.
   3. Sample file is downloaded from: http://cs.wheatonma.edu/mgousie/comp345/inputOS4.txt

*/

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
int currentSizeOfMemoryUsage = 0; //global integer to count for the current size of the memory usage;
int skipJob = 0; //global integer to count for number of job skipped;
int totalDeallocateProcesses = 0; //global integer to count for number of memory blocks remaining;

struct job {
	char op;
	int PID;
	int size;
	bool hasWrittenInMemoryBlock;
	bool hasNotPreviouslyBeenPushedInVector;
	int startAddress, endAddress;
};

/*
Function purpose (Pass by value): 
1. readFile from the user typed file name
2. Open the file and allocate/deallocate memory based on the file input to the vector<job>
3. Calculate memory usage during the allocate/deallocate process

Input: fileName

Output: 
1. PID that did not fit in memory
2. Return vector<job>

*/

vector<job> readFile(string inFileName) {
	ifstream FIN;
	FIN.open(inFileName);

	vector <job> memoryCalculator; //declares a vector container of type job called memoryCalculator;
	job thisJob; //Variable declaration: declare thisJob of type job;
	size_t vectorSize; //Vector size declaration: declare the vectorSize as it is guaranteed to be able to express the maximum size of the vector;
	bool hasFreeMemoryBlock = false; //status control: start of from as for there is no free memory block
	FIN >> thisJob.op;

	while (thisJob.op != 'Q') {
		FIN >> thisJob.PID;
		if ( thisJob.op == 'A' ) {
			thisJob.hasNotPreviouslyBeenPushedInVector = true; //start of as the job has not been pushed in vector;
			FIN >> thisJob.size;

			/* No free memory available */
			if ( totalDeallocateProcesses == 0 ) {// Counter for number of memory blocks available. 
			 	currentSizeOfMemoryUsage = currentSizeOfMemoryUsage + thisJob.size; //add on this job's size;
			 	//if after adding this job's size is <= than memory size, I push this job at the back;
			 	if ( currentSizeOfMemoryUsage <= MEMORY_SIZE ) {
			 		memoryCalculator.push_back(thisJob); //add at the back;
			 		thisJob.hasNotPreviouslyBeenPushedInVector = false; //change status
			 	}//if
			 	else {// If there is not enough memory, then skip this job;
					skipJob ++; // Total of SkipPID counter: in order to get status for number of processes that did not fit in memory;
					currentSizeOfMemoryUsage = currentSizeOfMemoryUsage - thisJob.size; //delete this job's size because I added before;
					cout << "======================================" << endl;
					cout << "PID " << thisJob.PID << " is skipped." << endl; // somehow need to track with their PID;
					cout << "======================================" << endl;
			 	}
			}//if no free memory available;

			else {/* there is free memory chunk available */
				// If this PID <= free memory; then push this PID at this free memory location;
			 	for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
					if (memoryCalculator[i].PID == -1) {// if there are memory chunks/ there is memory chunk;
						if (thisJob.size <= memoryCalculator[i].size) {// if this job size is less or equal than the earliest memory chunk;
							//begin inserting;
							memoryCalculator.insert(memoryCalculator.begin()+i, thisJob);//insert job at this memory chunk;
							thisJob.hasNotPreviouslyBeenPushedInVector = false; //change status;
							//change the memory size for that memory chunk;
							memoryCalculator[i+1].size = memoryCalculator[i+1].size - thisJob.size;
							break; //exit the loop
						}//if
				    }//if;    
				}//for

				/*  if after adding the new PID's size into the -1 memory chunk and there are no more free memory remaining 
				 	Then deleating that free memory chunk  */
				for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
					if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i].size == 0) ) {
						memoryCalculator.erase(memoryCalculator.begin()+i);
						totalDeallocateProcesses --; //change status of number of free memory blocks remaining;
					}//if
				}//for

				/*	If there are free memory chunk available but this job's size is larger than the memory chunk 
					First, count the totalCurrent MemoryUsage size. 
					If (after adding this job's size and it is less than the memory size)
						push this job at the back
					else
						skip this job;
				*/
				if (thisJob.hasNotPreviouslyBeenPushedInVector == true) {
					currentSizeOfMemoryUsage = currentSizeOfMemoryUsage + thisJob.size;
			 		if ( currentSizeOfMemoryUsage <= MEMORY_SIZE ) {
			 			memoryCalculator.push_back(thisJob);//push this job at the back of the vector
						thisJob.hasNotPreviouslyBeenPushedInVector = false;
			 		}
			 		else {
			 			skipJob ++; // in order to get status for number of processes that did not fit in memory;
						// track with their PID;
						currentSizeOfMemoryUsage = currentSizeOfMemoryUsage - thisJob.size;
						cout << "======================================" << endl;
						cout << " PID " << thisJob.PID << " is skipped." << endl;
						cout << "======================================" << endl;
			 		}//else
			 	}//if;

			}//else there is free memory available;

		}//if thisJob.op == 'A'

		else {//op == 'D'
			/* Deallocate memory: Change the status of this PID to -1 indicating this is memory block available */
			for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
				if (memoryCalculator[i].PID == thisJob.PID ) {
					memoryCalculator[i].PID = -1;
					memoryCalculator[i].op = 'D';
					hasFreeMemoryBlock = true;
					totalDeallocateProcesses ++;
					break; //exit the for loop
				}
			}

			/* Colasing contiguous blocks when memory is deallocated */
			for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i) {
				if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i+1].PID == -1) ) {
					memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
					memoryCalculator.erase(memoryCalculator.begin() + i + 1); //delete the i+1's memory block;
					totalDeallocateProcesses --; //update status
					i--; // in case there are three memory blocks coexisting after reading in one of the op == 'D'
				}//if	
			}//for

		}//else op == 'D'

		FIN >> thisJob.op; //read another job
	}//while

	FIN.close();
	
	return memoryCalculator;

}

/*

Function purpose (Pass by value): 
1. 	Print out the memory usage status including the actual memory table, number of processes did not fit in memory; 
	Total amount of memory in use; Total amount of memory remaining; Number of contiguous spaces; Average size of remaining memory blocks.

Input: The vector container of type job called memoryCalculator;
Output: 
1. Various status listed above

*/

void printStatus(vector<job> memoryCalculator) {

	cout << " " << endl;
	cout << " " << endl;

	//BEGIN: output table part
	memoryCalculator[0].startAddress = 0;
	memoryCalculator[0].endAddress = memoryCalculator[0].size - 1;
	cout << setw(23) << "Memory Table" << endl;	
	cout << "======================================" << endl;
	cout << setw(4) << "PID" << setw(10) << "Start" << setw(10) <<"End" << setw(10) << "Size" << endl;

	//print the first job's PID, startAddress, endAddress, size as the first job's information will be used for the later job.
    cout << setw(4) << memoryCalculator[0].PID << setw(10);
    cout << memoryCalculator[0].startAddress << setw(10);
	cout << memoryCalculator[0].endAddress << setw(10);
	cout << memoryCalculator[0].size << setw(10) << endl;


	int maxNumberOfProcessInVector; 
    for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		memoryCalculator[i].startAddress = memoryCalculator[i-1].endAddress + 1; //the second start address is based on the first's endAddress;
		memoryCalculator[i].endAddress = memoryCalculator[i].startAddress + memoryCalculator[i].size - 1; //the second's end is based on the second's size and begin address;
		cout << setw(4) << memoryCalculator[i].PID << setw(10);
		cout << memoryCalculator[i].startAddress << setw(10);
		cout << memoryCalculator[i].endAddress << setw(10);
		cout << memoryCalculator[i].size << setw(10) << endl;
		maxNumberOfProcessInVector = i;
	}

	//the last remaining spaces
	cout << setw(4) << -1 << setw(10);
	cout << memoryCalculator[maxNumberOfProcessInVector].endAddress + 1 << setw(10); // Free remaining memory startaddress 
	cout << MEMORY_SIZE << setw(10);
	int lastMemoryChunkSize = MEMORY_SIZE - (memoryCalculator[maxNumberOfProcessInVector].endAddress + 1) + 1; //calculate the last memory chunk size;
	cout << lastMemoryChunkSize << setw(10) << endl;	

	cout << "======================================" << endl;
	// END: output table part
	
	// BEGIN: Calculate number of processes that did not fit in memory (skipJob is a global counter);
	cout << "Number of processes that is skipped is: " << skipJob << endl;
	// END

	// BEGIN: calculate total amount of memory in use at the end of the simulation;
	int memoryInUse = 0;
	for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		if (memoryCalculator[i].PID != -1) {
			memoryInUse = memoryCalculator[i].size + memoryInUse;
		}
	}//for
	memoryInUse += memoryCalculator[0].size;
	cout << "Total amount of memory in use at the end of the simulation is: " << memoryInUse << " bytes."<< endl;
	//END

	//BEGIN: calculate total amount of memory remaining
	int memoryRemaining = 0;
	for (int i = 1, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
		if (memoryCalculator[i].PID == -1) {
			memoryRemaining = memoryCalculator[i].size + memoryRemaining;
		}
	}//for
	memoryRemaining += lastMemoryChunkSize; //need to add on the last memory chunk size;
	cout << "Total amount of memory remaining is: " << memoryRemaining << " bytes."<< endl;
	//END

	//BEGIN: print of number of memory blocks left
	totalDeallocateProcesses += 1; // add one because I also need to count the free space left in the end;
	cout << "Number of contiguous spaces (memory blocks) remaining is: " << totalDeallocateProcesses << endl;
	//EMD

	//BEGIN: Calculate average size of remaining memory blocks
	float memoryBlockAverageSize = (float) memoryRemaining / (float)totalDeallocateProcesses;
	cout << "Average size of remaining memory blocks is: " << memoryBlockAverageSize << " bytes."<< endl;
	//END;


} //void printStatus;


int main () {

	int fileNumber;
	string fileName;
	cout << "Type in the name of the input file: ";
	cin >> fileName;
	vector<job> memoryCalculator = readFile(fileName);
	printStatus(memoryCalculator);
	return 0;

}




