// // vector 13 version: 
// last edit: 11/16: 0:04
// Just need to do couple calculations:
// For example; number of processes and their PIDs that did not fit in memory;
// Total amount of memory in use at the end of the simulation;
// Total amount of remaining memory;
// Number of contiguous spaces (memory blocks) remaining
// Average size of remaining memory blocks

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
int totalDeallocateProcesses = 0;

struct job {
	char op;
	int PID;
	int size;
	bool hasWrittenInMemoryBlock;
	bool hasNotPreviouslyBeenPushedInVector;
	int startAddress, endAddress;
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
		// vector <int>::iterator intVecIter; //in order to use insert function;
		job thisJob;
		size_t vectorSize;
		bool hasFreeMemoryBlock = false;
		// char fop; int fPID, fsize;
		myFile >> thisJob.op;

		while ( thisJob.op != 'Q') {
			myFile >> thisJob.PID;
			if ( thisJob.op == 'A') {
				thisJob.hasNotPreviouslyBeenPushedInVector = true;
				myFile >> thisJob.size;
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
						cout << "PID " << thisJob.PID << " is skipped." << endl;
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
							cout << "PID " << thisJob.PID << " is skipped." << endl;
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
			

			myFile >> thisJob.op;


		}//while;

		cout << " " << endl;
		cout << "*********** End the while loop ***********" << endl;
		cout << "*********** now print out elements in vector: ***********" << endl;

		cout << " " << endl;



		memoryCalculator[0].startAddress = 0;
		memoryCalculator[0].endAddress = memoryCalculator[0].size - 1;

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
		cout << MEMORY_SIZE - (memoryCalculator[maxNumberOfProcessInVector].endAddress + 1) + 1 << setw(10) << endl;		


		cout << "total PID = -1 is: " << totalDeallocateProcesses << endl;




		myFile.close();
		

	}



	else {
		cout << "Sorry. Cannot locate your file." << endl;
	}
	cout << "total size is: " << totalSize << endl;
	

}









