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

struct job {
	char op;
	int PID;
	int size;
	bool hasWrittenInMemoryBlock;
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

				if ( totalSize < MEMORY_SIZE ) {
					if ( hasFreeMemoryBlock == true ) { // need debug: if there are any free memory chunk; or if there are any memory chunk;
						//add statement, if the -1 mark is marked contigiously
												//combine these spaces together;

						//search the whole vector to see memory blocks;
						// for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
						// 	if (memoryCalculator[i].PID == -1) {// if there are memory chunks/ there is memory chunk;
						// 		if (thisJob.size <= memoryCalculator[i].size) {
						// 			//begin inserting;
						// 			memoryCalculator.insert(memoryCalculator.begin()+i, thisJob);//insert at position 2 for D3 statement;
						// 			job modifiedJob;
						// 			modifiedJob.op = 'D';
						// 			modifiedJob.PID = -1;

						// 			modifiedJob.size = memoryCalculator[i+1].size - thisJob.size;
						// 			memoryCalculator.erase(memoryCalculator.begin()+i+1); //erase the -1 part of the memory;
						// 			memoryCalculator.insert(memoryCalculator.begin()+i+1, modifiedJob);
						// 			totalSize = totalSize - thisJob.size; // modified the total size in memory since you are inserting in your free memory chunk;
						// 			break; // exit the for loop after inserting thisJob;

						// 		}//if
						// 		else {
						// 			memoryCalculator.push_back(thisJob);
						// 		}

					 //    	}//if;
						// }//for




						//search the whole vector to see memory blocks;
						for (int i = 0, vectorSize = memoryCalculator.size(); i < vectorSize; ++i ) {
							if (memoryCalculator[i].PID == -1) {// if there are memory chunks/ there is memory chunk;
								if (thisJob.size <= memoryCalculator[i].size) {
									//begin inserting;
									memoryCalculator.insert(memoryCalculator.begin()+i, thisJob);//insert at position 2 for D3 statement;
									//change the memory size for that memory chunk;
									memoryCalculator[i+1].size = memoryCalculator[i+1].size - thisJob.size;
									// memoryCalculator[memoryCalculator.begin()+i+1].size -= thisJob.size;
									totalSize = totalSize - thisJob.size;
									break;
								}


								else {
									memoryCalculator.push_back(thisJob);
								}

					    	}//if;
						}//for




						
					}
					else {// if there arn't any free memory chunk OR memory chunk is less than PID size;
						memoryCalculator.push_back(thisJob);

					}


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











