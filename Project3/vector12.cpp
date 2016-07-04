// vector 12 version: 
// debug: should merge free memory chunk together

// debug : line 54 for the allcoate part. If there are any free memory exists; then you should not skip that job. Instead, you should add that job in the memory part;

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
				

				if ( totalSize <= MEMORY_SIZE ) { // THIS PART NEED DEBUG. WHAT IF THERE ARE ALREADY FREE MEMORY CHUNK?? THEN YOU CANNOT GO FOR THE MEMORY CHUNK;
					thisJob.hasNotPreviouslyBeenPushedInVector = true;
					if ( hasFreeMemoryBlock == true ) { // need debug: if there are any free memory chunk; or if there are any memory chunk;
						//add statement, if the -1 mark is marked contigiously
												//combine these spaces together;
						//search the whole vector to see free memory blocks;
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

						// if after adding the new PID's size into the -1 memory chunk; I am deleating that free memory chunk;
						for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
							if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i].size == 0) ) {
								memoryCalculator.erase(memoryCalculator.begin()+i);
								totalDeallocateProcesses --;
							}//if
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
				

			}// if op == 'A'
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
			

			/**** delete the vector space if PID == -1 and size == 0; *****/
			// for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
			// 	if ( (memoryCalculator[i].PID == -1) && (memoryCalculator[i].size == 0) ) {
			// 		memoryCalculator.erase(memoryCalculator.begin()+i);
			// 	}//if
			// }//for


		// if (!pSkipped) {
  //           i = 0; //incrementer to find p in ram
  //           while ((i < ram.size()) && (ram[i]->processID != p->processID)) { //while i isn't past ram size and block isn't p
  //               i++;
  //           }

  //           ram[i]->processID = -1; //set process p's id to be -1 (free space now)

  //           if (i+1 < ram.size()) { //if block after old p in ram is free, join them
  //               if (ram[i+1]->processID == -1) {
  //                   ram[i]->size = ram[i]->size + ram[i+1]->size; //old p size = old p size + free block size
  //                   ram[i]->endAddress = ram[i+1]->endAddress; //old p end address = i+1 free block's end address
  //                   ram.erase(ram.begin()+i+1); //delete ram[i+1] so we now have 1 free block
  //               }
  //           }
  //           if (i-1 >= 0) { //if block before old p in ram is free, join them (same process as above but with i-1 and i instead of i and i+1)
  //               if (ram[i-1]->processID == -1) {
  //                   ram[i-1]->size = ram[i-1]->size + ram[i]->size;
  //                   ram[i-1]->endAddress = ram[i]->endAddress;
  //                   ram.erase(ram.begin()+i); //delete ram[i] == p
  //               }
  //           }
  //       }

			// for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
			// 	if ( memoryCalculator[i].PID == memoryCalculator[i+1].PID ) {
			// 		memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
			// 		memoryCalculator.erase(memoryCalculator.begin()+i+1);
			// 	}
			// }

			// this part needs debug
			// The debugging part is to combine all free memory spaces
			// Debugging part: if there are couple memory blocks, and they are next to each other, we should merge all memory blocks
			// question: how do I restart a for loop
			// cout << "memory size: " <<  memoryCalculator.size() << endl;
			// for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
			// // cout << "memory size: " <<  memoryCalculator.size() << endl;
			// // int j = i;
			// 	if (memoryCalculator[i].PID == memoryCalculator[i+1].PID) {
			// 		cout << "debug " << i << endl;
			// 		// memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
			// 		// memoryCalculator.erase(memoryCalculator.begin() + i );
			// 		memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
			// 		//memoryCalculator.erase(memoryCalculator.begin() + (i + 1));
			// 		// memoryCalculator.erase(memoryCalculator[i+1]);
			// 		memoryCalculator.erase (memoryCalculator.begin()+i);
			// 		i--;
			// 	}
			// }//for


			myFile >> thisJob.op;

			// cout << "memory size: " <<  memoryCalculator.size() << endl;


			// while there are more than one -1 as PID; and their position are next to each other
			// 	using a for loop to combine those two PIDs
			// int i = 0;
			// while ( totalDeallocateProcesses > 1 && memoryCalculator[i].PID == memoryCalculator[i].PID ) {
				// for ( int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
				// 	memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
				// 	memoryCalculator.erase(memoryCalculator.begin() + i);
				// 	totalDeallocateProcesses --;
				// }//for
			// }//while
			// cout << "1" << endl;
			// while ( totalDeallocateProcesses > 1 ) {
			// 	cout << "2" << endl;
				// for (int j = 0, vectorSize = memoryCalculator.size(); j < vectorSize; ++j ) {
				// 	if (memoryCalculator[j].PID == memoryCalculator[j+1].PID) {
				// 		memoryCalculator[j].size = memoryCalculator[j].size + memoryCalculator[j+1].size;
				// 		memoryCalculator.erase(memoryCalculator.begin() + j+1);
				// 		totalDeallocateProcesses --;
				// 		// break;
				// 	}
				// 	// break;
				// }
			// }


			// int i = 0;
			// vectorSize = memoryCalculator.size();
			// while ( i < vectorSize - 1) {
			// 	int j;
				// for (int j = 0, vectorSize = memoryCalculator.size(); j < vectorSize; ++j ) {
				// 	if (memoryCalculator[j].PID == memoryCalculator[j+1].PID) {
				// 		memoryCalculator[j].size = memoryCalculator[j].size + memoryCalculator[j+1].size;
				// 		memoryCalculator.erase(memoryCalculator.begin() + j+1);
				// 	}
				// 	// break;
				// 	// j --;
				// }
				// i = j;
				// cout << i << endl;
				
			// }

			// while ( i < vectorSize ) {
			// 	int runlength = 1; 
			// 	while ( i + runlength <= )
			// }


			// int i = 0;
			// vectorSize = memoryCalculator.size();
			// while ( i < vectorSize ) {
			// 	if ( memoryCalculator[i].PID == memoryCalculator[i+1].PID ) {
			// 		memoryCalculator[i].size = memoryCalculator[i].size + memoryCalculator[i+1].size;
			// 		memoryCalculator.erase(memoryCalculator.begin()+i+1);
			// 	}

			// 	i ++;
			// }




 		// 	while ((i < ram.size()) && (ram[i]->processID != p->processID)) { //while i isn't past ram size and block isn't p
   //              i++;
   //          }

   //          ram[i]->processID = -1; //set process p's id to be -1 (free space now)

   //          if (i+1 < ram.size()) { //if block after old p in ram is free, join them
   //              if (ram[i+1]->processID == -1) {
   //                  ram[i]->size = ram[i]->size + ram[i+1]->size; //old p size = old p size + free block size
   //                  ram[i]->endAddress = ram[i+1]->endAddress; //old p end address = i+1 free block's end address
   //                  ram.erase(ram.begin()+i+1); //delete ram[i+1] so we now have 1 free block
   //              }
   //          }
   //          if (i-1 >= 0) { //if block before old p in ram is free, join them (same process as above but with i-1 and i instead of i and i+1)
   //              if (ram[i-1]->processID == -1) {
   //                  ram[i-1]->size = ram[i-1]->size + ram[i]->size;
   //                  ram[i-1]->endAddress = ram[i]->endAddress;
   //                  ram.erase(ram.begin()+i); //delete ram[i] == p
   //              }
   //          }


   //          int i;
			// vectorSize = memoryCalculator.size();
   //          while ( i < vectorSize &&)





		}//while;

		cout << " " << endl;
		cout << "*********** End the while loop ***********" << endl;
		cout << "*********** now print out elements in vector: ***********" << endl;

		cout << " " << endl;


		// this is just debugging statement to make sure my vector called memoryCalculator is working properly;
		for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
			cout << "\tOP: " << memoryCalculator[i].op << " ";
	        cout << "\tPID: " << memoryCalculator[i].PID <<" ";
	        cout << "\tSize: " << memoryCalculator[i].size << endl;
		}
		cout << "total PID = -1 is: " << totalDeallocateProcesses << endl;
		myFile.close();
		

	}
	else {
		cout << "Sorry. Cannot locate your file." << endl;
	}
	cout << "total size is: " << totalSize << endl;
	

}











